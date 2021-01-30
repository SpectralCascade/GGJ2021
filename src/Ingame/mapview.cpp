#include "mapview.h"
#include "explorer.h"
#include "UI/PlacementButton.h"
#include "GameController.h"
#include "terrain.h"

using namespace std;

REGISTER_COMPONENT(MapView);

void MapView::OnLoadFinish()
{
    grid = entity->FindAndGetComponent<GridLayout>("MapGrid", entity);
    if (grid != nullptr)
    {
        box = grid->GetEntity()->GetComponent<BoxLayout>();
    }

    gc = entity->FindAndGetComponent<GameController>("Root");

    fundsText = entity->FindAndGetComponent<Text>("FundsText");
    progressText = entity->FindAndGetComponent<Text>("MapCompletion");

    explorerParent = entity->Find("ExplorerParent");

    moveTimer.Stop();

#ifndef OSSIUM_EDITOR
    UpdateText();
    GenerateMap();
    // TODO: remove me, should only spawn on map load from hiring menu
    SpawnExplorer(entity->FindAndGetComponent<Explorer>("1"));
#endif

}

void MapView::ClearMap()
{
    for (unsigned int i = 0, counti = zones.size(); i < counti; i++)
    {
        for (unsigned int j = 0, countj = zones[i].size(); j < countj; j++)
        {
            zones[i][j]->AddComponentOnce<Texture>()->SetSource(nullptr);
        }
    }
    zones.clear();
}

void MapView::GenerateMap()
{
    ClearMap();
    zones.reserve(grid->cols);
    for (unsigned int i = 0, counti = grid->cols; i < counti; i++)
    {
        zones.push_back(vector<Entity*>(grid->rows));
        for (unsigned int j = 0, countj = grid->rows; j < countj; j++)
        {
            auto cell = grid->GetCellElement(i, j);

            zones[i][j] = cell->GetEntity()->CreateChild();

            // Randomly generate the terrain type
            Terrain* terrain = zones[i][j]->AddComponentOnce<Terrain>();
            float terrainChance = gc->rng->Float();
            if (terrainChance < 0.35f)
            {
                terrain->terrain = TERRAIN_PLAIN;
            }
            else if (terrainChance < 0.55f)
            {
                terrain->terrain = TERRAIN_FOREST;
            }
            else if (terrainChance < 0.75f)
            {
                terrain->terrain = TERRAIN_HILL;
            }
            else if (terrainChance < 0.95f)
            {
                terrain->terrain = TERRAIN_MOUNTAIN;
            }
            else
            {
                terrain->terrain = TERRAIN_LAKE;
            }
            terrain->Init(gc);

            PlacementButton* dragButton = cell->GetEntity()->AddComponentOnce<PlacementButton>();
            dragButton->OnLoadFinish();

            dragButton->OnClicked += [&, i, j] (Button& caller) {
                SelectCell(i, j);
            };

        }
    }
}

void MapView::Render(Renderer& renderer)
{
    if (grid != nullptr && box != nullptr)
    {
        Vector2 boxDim = box->GetInnerDimensions();
        Vector2 pos = GetTransform()->GetWorldPosition();
        pos -= (boxDim * 0.5f);
        Line drawLine(pos, Vector2(pos.x, pos.y + boxDim.y));
        float fraction = boxDim.x / (float)grid->cols;
        for (unsigned int col = 0, cols = grid->cols + 1; col < cols; col++)
        {
            drawLine.a.x = pos.x + ((float)col * fraction);
            drawLine.b.x = drawLine.a.x;
            drawLine.Draw(renderer, gridColor);
        }
        drawLine.a.x = pos.x;
        drawLine.b.x = pos.x + boxDim.x;
        fraction = boxDim.y / (float)grid->rows;
        for (unsigned int row = 0, rows = grid->rows + 1; row < rows; row++)
        {
            drawLine.a.y = pos.y + ((float)row * fraction);
            drawLine.b.y = drawLine.a.y;
            drawLine.Draw(renderer, gridColor);
        }

        // Now draw selected grid cell highlight
        if (selectedX >= 0 && selectedY >= 0)
        {
            if ((unsigned int)selectedX >= grid->cols || (unsigned int)selectedY >= grid->rows)
            {
                // Make sure selected is always valid
                Log.Warning("Selected cell at ({0}, {1}) is invalid! Grid size = ({2}, {3})", selectedX, selectedY, grid->cols, grid->rows);
                selectedX = -1;
                selectedY = -1;
            }
            else
            {
                float width = boxDim.x / (float)grid->cols;
                Rect highlight(pos.x + (width * selectedX) + 1, pos.y + (fraction * selectedY) + 1, width - 1.0f, fraction - 1.0f);
                highlight.Draw(renderer, Colors::WHITE);
            }
        }

    }
}

void MapView::SpawnExplorer(Explorer* explorer)
{
    // TODO: randomise spawn zone?
    explorerZone[0] = 0;
    explorerZone[1] = 0;

    // Destroy old explorer
    if (hiredExplorer != nullptr)
    {
        hiredExplorer->GetEntity()->Destroy();
        hiredExplorer = nullptr;
    }

    // Spawn hired explorer
    hiredExplorer = explorer->GetEntity()->Clone(explorerParent)->GetComponent<Explorer>();
    hiredExplorer->GetEntity()->GetComponent<BoxLayout>()->Destroy();

    auto resources = entity->GetService<ResourceController>();
    auto renderer = entity->GetService<Renderer>();

    hiredExplorer->hat = hiredExplorer->GetEntity()->CreateChild()->AddComponentOnce<Texture>();
    hiredExplorer->stache = hiredExplorer->GetEntity()->CreateChild()->AddComponentOnce<Texture>();
    hiredExplorer->face = hiredExplorer->GetEntity()->AddComponentOnce<Texture>();
    hiredExplorer->hat->SetSource(resources->Get<Image>(hiredExplorer->hatPath, *renderer), true);
    hiredExplorer->stache->SetSource(resources->Get<Image>(hiredExplorer->stachePath, *renderer), true);
    hiredExplorer->face->SetSource(resources->Get<Image>(hiredExplorer->facePath, *renderer), true);
    hiredExplorer->resText = entity->FindAndGetComponent<Text>("Health");
    hiredExplorer->luckText = nullptr;
    hiredExplorer->speedText = nullptr;

    // Update appearance
    hiredExplorer->UpdateAppearance();
    
    hiredExplorer->GetTransform()->SetWorldPosition(grid->GetCellElement(explorerZone[0], explorerZone[1])->GetTransform()->GetWorldPosition());
    hiredExplorer->GetEntity()->SetActive(true);

    zones[explorerZone[0]][explorerZone[1]]->GetComponent<Terrain>()->Discover();
    TryMoveToZone(explorerZone[0], explorerZone[1]);
}

void MapView::UpdateText()
{
    if (gc != nullptr)
    {
        if (fundsText != nullptr)
        {
            fundsText->text = Utilities::Format("Funds: ${0}", gc->funds);
            fundsText->dirty = true;
        }
        if (progressText != nullptr)
        {
            progressText->text = Utilities::Format("Map Progress: {0}%", (int)(100.0f * ((float)discovered / (float)(grid->rows * grid->cols))));
        }
    }
}

void MapView::Update()
{
    if (moveTimer.IsStarted())
    {
        float seconds = (float)moveTimer.GetTicks() / 1000.0f;
        if (seconds > 3)
        {
        }
        oldTime = seconds;
    }
    else
    {
        oldTime = 0;
    }
}

void MapView::SelectCell(int i, int j)
{
    selectedX = (int)i;
    selectedY = (int)j;
    if (i >= 0 && j >= 0)
    {
        if (TryMoveToZone(i, j) != nullptr)
        {
            // Move explorer
            // TODO: lerp!
            moveTimer.Start();
            hiredExplorer->GetTransform()->SetWorldPosition(grid->GetCellElement(explorerZone[0], explorerZone[1])->GetTransform()->GetWorldPosition());
            explorerZone[0] = i;
            explorerZone[1] = j;
        }
    }
}

Terrain* MapView::TryMoveToZone(int i, int j)
{
    Terrain* zone = zones[i][j]->GetComponent<Terrain>();
    if (!zone->IsDiscovered())
    {
        return nullptr;
    }
    else
    {
        // Explore surrounding zones
        if (i - 1 >= 0)
        {
            zones[i - 1][j]->GetComponent<Terrain>()->Discover();
        }
        if (i + 1 < (int)grid->cols)
        {
            zones[i + 1][j]->GetComponent<Terrain>()->Discover();
        }
        if (j - 1 >= 0)
        {
            zones[i][j - 1]->GetComponent<Terrain>()->Discover();
        }
        if (j + 1 < (int)grid->rows)
        {
            zones[i][j + 1]->GetComponent<Terrain>()->Discover();
        }
        return zone;
    }
}
