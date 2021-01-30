#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <Ossium.h>

using namespace Ossium;

class Explorer;

struct MapViewSchema : public Schema<MapViewSchema, 20>
{
    DECLARE_BASE_SCHEMA(MapViewSchema, 20);
    
    SDL_Color gridColor = {0, 0, 0, 60};

};

class GameController;

class MapView : public GraphicComponent, public MapViewSchema
{
public:
    CONSTRUCT_SCHEMA(GraphicComponent, MapViewSchema);
    DECLARE_COMPONENT(GraphicComponent, MapView);
    
    void OnLoadFinish();

    void GenerateMap();

    void ClearMap();

    void Render(Renderer& renderer);

    void SelectCell(int i, int j);

    GridLayout* grid = nullptr;
    BoxLayout* box = nullptr;

    int selectedX = -1;
    int selectedY = -1;

    // Array of all zones in the grid.
    std::vector<std::vector<Entity*>> zones;

    int targetZone[2];

    Explorer* hiredExplorer = nullptr;

    GameController* gc = nullptr;

};


#endif // MAPVIEW_H
