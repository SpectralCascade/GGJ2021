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

#ifndef OSSIUM_EDITOR
    GenerateMap();
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

void MapView::SelectCell(int i, int j)
{
    selectedX = (int)i;
    selectedY = (int)j;
    if (i >= 0 && j >= 0)
    {
        zones[i][j]->GetComponent<Terrain>()->Discover();
    }
}
