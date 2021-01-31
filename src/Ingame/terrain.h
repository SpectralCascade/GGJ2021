#ifndef TERRAIN_H
#define TERRAIN_H

#include <Ossium.h>

class GameController;

using namespace Ossium;

enum TerrainType
{
    TERRAIN_NONE = 0,
    TERRAIN_PLAIN = 1,
    TERRAIN_FOREST = 2,
    TERRAIN_LAKE = 4,
    TERRAIN_HILL = 8,
    TERRAIN_MOUNTAIN = 16
};

struct TerrainSchema : public Schema<TerrainSchema, 20>
{
    DECLARE_BASE_SCHEMA(TerrainSchema, 20);
    
    M(int, terrain) = TERRAIN_PLAIN;

};


class Terrain : public Component, public TerrainSchema
{
public:
    CONSTRUCT_SCHEMA(Component, TerrainSchema);
    DECLARE_COMPONENT(Component, Terrain);

    void Init(GameController* gc);

    void Discover();

    bool IsDiscovered();
    
    void Update();

private:
    GameController* game = nullptr;

    bool discovered = false;

    float delta = 0.0f;

    Texture* tex = nullptr;

    BoxLayout* parentBox = nullptr;
    
};


#endif // TERRAIN_H
