#include "terrain.h"
#include "GameController.h"

REGISTER_COMPONENT(Terrain);

void Terrain::Init(GameController* gc)
{
    auto resources = entity->GetService<ResourceController>();
    auto renderer = entity->GetService<Renderer>();

    game = gc;

    tex = entity->AddComponentOnce<Texture>();
    //tex->fitLayout = 4;
    tex->OnLoadFinish();

    // Blank out tiles that haven't been explored
    tex->SetSource(resources->Get<Image>("assets/Sprites/blankcell.png", *renderer));
    tex->SetAlphaMod(100);
    discovered = false;

    parentBox = entity->GetParent()->GetComponent<BoxLayout>();

}

void Terrain::Update()
{
    if (discovered && tex != nullptr && tex->GetMod().a < 255 && game != nullptr)
    {
        // Fade in
        delta = game->clock.GetDeltaTime();
        tex->SetAlphaMod((Uint8)Utilities::Clamp((int)tex->GetMod().a + 5, 0, 255));
    }
}

void Terrain::Discover()
{
    if (discovered)
    {
        return;
    }

    auto resources = entity->GetService<ResourceController>();
    auto renderer = entity->GetService<Renderer>();

    discovered = true;
    if (tex != nullptr)
    {        
        switch (terrain)
        {
        case TERRAIN_PLAIN:
            tex->SetSource(nullptr);
            break;
        case TERRAIN_FOREST:
            tex->SetSource(resources->Get<Image>("assets/Sprites/trees1.png", *renderer));
            break;
        case TERRAIN_LAKE:
            tex->SetSource(resources->Get<Image>("assets/Sprites/lake.png", *renderer));
            break;
        case TERRAIN_HILL:
            tex->SetSource(resources->Get<Image>("assets/Sprites/hills.png", *renderer));
            break;
        case TERRAIN_MOUNTAIN:
            tex->SetSource(resources->Get<Image>("assets/Sprites/mountain1.png", *renderer));
            break;
        }
    }
}

bool Terrain::IsDiscovered()
{
    return discovered;
}
