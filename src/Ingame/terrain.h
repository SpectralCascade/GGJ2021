#ifndef TERRAIN_H
#define TERRAIN_H

#include <Ossium.h>

using namespace Ossium;

enum TerrainType
{
    TERRAIN_MOUNTAIN = 0,
    TERRAIN_FOREST,
    TERRAIN_LAKE,
    TERRAIN_PLAIN
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

    void OnLoadFinish();

    void Init();

    Texture* tex;
    
};


#endif // TERRAIN_H
