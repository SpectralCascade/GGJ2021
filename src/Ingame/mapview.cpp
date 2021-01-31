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
    DEBUG_ASSERT(gc != nullptr);
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
    Entity* spawned = explorerParent->CreateChild();
    hiredExplorer = spawned->AddComponentOnce<Explorer>();
    hiredExplorer->FromString(explorer->ToString());

    auto resources = entity->GetService<ResourceController>();
    auto renderer = entity->GetService<Renderer>();

    spawned->AddComponentOnce<Transform>();
    hiredExplorer->face = spawned->AddComponentOnce<Texture>();
    hiredExplorer->face->OnLoadFinish();
    hiredExplorer->face->SetSource(resources->Get<Image>(hiredExplorer->facePath, *renderer), true);
    hiredExplorer->face->SetRenderWidth(0.5f);
    hiredExplorer->face->SetRenderHeight(0.5f);

    auto hat = hiredExplorer->GetEntity()->CreateChild();
    hat->AddComponentOnce<Transform>();
    hiredExplorer->hat = hat->AddComponentOnce<Texture>();
    hiredExplorer->hat->OnLoadFinish();
    hiredExplorer->hat->SetSource(resources->Get<Image>(hiredExplorer->hatPath, *renderer), true);

    auto stache = hiredExplorer->GetEntity()->CreateChild();
    stache->AddComponentOnce<Transform>();
    hiredExplorer->stache = stache->AddComponentOnce<Texture>();
    hiredExplorer->stache->OnLoadFinish();
    hiredExplorer->stache->SetSource(resources->Get<Image>(hiredExplorer->stachePath, *renderer), true);

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
    if (moveTimer.IsStarted() && hiredExplorer != nullptr)
    {
        float seconds = (float)moveTimer.GetTicks() / 1000.0f;
        
        if ((seconds >= 0.33f && oldTime < 0.33f) || (seconds >= 0.66f && oldTime < 0.66f) || (seconds >= 1.0f && oldTime < 1.0f))
        {
            auto resources = entity->GetService<ResourceController>();
            string filename;
            int footnumber = gc->rng->Int(0, 5) + 1;

            switch (hiredExplorer->tier)
            {
            case 0:
                filename = "Light";
                break;
            case 1:
                filename = "Medium";
                break;
            case 2:
                filename = "Heavy";
                break;
            }

            gc->footsteps->Play(resources->Get<AudioClip>(Utilities::Format("assets/Audio/Footsteps/FS_{0}0{1}.wav", filename, footnumber)));
        }
        if (seconds > 1.0f)
        {
            // Finished moving
            hiredExplorer->GetTransform()->SetWorldPosition(grid->GetCellElement(explorerZone[0], explorerZone[1])->GetTransform()->GetWorldPosition());            
            moveTimer.Stop();
            oldTime = 0;
        }
        else
        {
            Vector2 target = grid->GetCellElement(explorerZone[0], explorerZone[1])->GetTransform()->GetWorldPosition();
            Vector2 origin = grid->GetCellElement(previousZone[0], previousZone[1])->GetTransform()->GetWorldPosition();
            hiredExplorer->GetTransform()->SetWorldPosition(origin.Lerp(target, seconds / 1.0f));
            oldTime = seconds;
        }
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
        if (!moveTimer.IsStarted())
        {
            int cost = CostToZone(i, j);
            if (gc->funds >= cost)
            {
                if (TryMoveToZone(i, j) != nullptr)
                {
                    // Move explorer, take funds
                    moveTimer.Start();
                    previousZone[0] = explorerZone[0];
                    previousZone[1] = explorerZone[1];
                    explorerZone[0] = i;
                    explorerZone[1] = j;

                    gc->funds -= cost;
                    UpdateText();
                }
                else
                {
                    // TODO: Error noise
                }
            }
            else
            {
                // TODO: Error noise
            }
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

int MapView::CostToZone(int i, int j)
{
    Terrain* t = zones[i][j]->GetComponent<Terrain>();
    
    switch (t->terrain)
    {
    case TERRAIN_MOUNTAIN:
    case TERRAIN_LAKE:
        return 3;
    case TERRAIN_FOREST:
    case TERRAIN_HILL:
        return 2;
    case TERRAIN_PLAIN:
    default:
        return 1;
    }
}
