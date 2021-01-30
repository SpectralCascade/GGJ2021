#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <Ossium.h>

using namespace Ossium;

class Explorer;
class Terrain;

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

    void SpawnExplorer(Explorer* explorer);

    Terrain* TryMoveToZone(int i, int j);

    void Render(Renderer& renderer);

    void SelectCell(int i, int j);

    void UpdateText();

    void Update();

    Timer moveTimer;
    float oldTime = 0;

    GridLayout* grid = nullptr;
    BoxLayout* box = nullptr;

    int selectedX = -1;
    int selectedY = -1;

    // Array of all zones in the grid.
    std::vector<std::vector<Entity*>> zones;

    Entity* explorerParent = nullptr;
    Explorer* hiredExplorer = nullptr;

    Text* fundsText = nullptr;
    Text* progressText = nullptr;

    // Start in upper left corner
    int explorerZone[2] = {0, 0};
    int previousZone[2] = {0, 0};

    int discovered = 0;

    GameController* gc = nullptr;

};


#endif // MAPVIEW_H
