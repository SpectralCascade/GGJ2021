#include "explorer.h"

void Explorer::OnLoadFinish()
{
    hat = entity->FindAndGetComponent<Texture>("Hat", entity);
    stache = entity->FindAndGetComponent<Texture>("Stache", entity);
    face = entity->GetComponent<Texture>();

    resText = entity->FindAndGetComponent<Text>("Resilience", entity);
    luckText = entity->FindAndGetComponent<Text>("Luck", entity);
    speedText = entity->FindAndGetComponent<Text>("Speed", entity);

    UpdateAppearance();

}

void Explorer::UpdateAppearance()
{
    // Update character appearance
    auto resources = entity->GetService<ResourceController>();
    auto renderer = entity->GetService<Renderer>();

    if (face != nullptr)
    {
        face->SetSource(resources->Get<Image>(renderer, hatPath));
    }

    if (hat != nullptr)
    {
        hat->SetSource(resources->Get<Image>(renderer, hatPath));
    }

    if (stache != nullptr)
    {
        stache->SetSource(resources->Get<Image>(renderer, stachePath));
    }

    // Update stats text
    if (resText != nullptr)
    {
        resText->text = Utilities::Format("Resilience: {0}", resilience);
        resText->dirty = true;
    }
    if (speedText != nullptr)
    {
        speedText->text = Utilities::Format("Speed: {0}", speed);
        speedText->dirty = true;
    }
    if (luckText != nullptr)
    {
        luckText->text = Utilities::Format("Luck: {0}", luck);
        luckText->dirty = true;
    }
}