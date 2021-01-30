#ifndef EXPLORER_H
#define EXPLORER_H

#include <Ossium.h>

using namespace Ossium;

struct ExplorerMetaSchema : public Schema<ExplorerMetaSchema, 20>
{
    DECLARE_BASE_SCHEMA(ExplorerMetaSchema, 20);
    
    M(std::string, name) = "Harold";

    M(int, resilience) = 3;

    M(float, speed) = 1.0f;

    M(float, luck) = 0;

    M(unsigned int, cost) = 0;

    M(std::string, hatPath) = "assets/Sprites/hat.png";

    M(std::string, facePath) = "assets/Sprites/placeholderface.png";

    M(std::string, stachePath) = "assets/Sprites/stache.png";

};

struct ExplorerSchema : public ExplorerMetaSchema
{
    DECLARE_SCHEMA(ExplorerSchema, ExplorerMetaSchema);

    M(int, energy) = 3;

};

class Explorer : public Component, public ExplorerSchema
{
public:
    CONSTRUCT_SCHEMA(Component, ExplorerSchema);
    DECLARE_COMPONENT(Component, Explorer);
    
    void OnLoadFinish();

    void UpdateAppearance();

    Texture* hat = nullptr;
    Texture* stache = nullptr;
    Texture* face = nullptr;

    Text* resText = nullptr;
    Text* speedText = nullptr;
    Text* luckText = nullptr;
    
};


#endif // EXPLORER_H
