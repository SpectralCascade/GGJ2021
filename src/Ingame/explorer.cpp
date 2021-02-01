#include "explorer.h"

REGISTER_COMPONENT(Explorer);

void Explorer::OnLoadFinish()
{
    hat = entity->FindAndGetComponent<Texture>("Hat", entity);
    hair = entity->FindAndGetComponent<Texture>("Hair", entity);
    stache = entity->FindAndGetComponent<Texture>("Stache", entity);
    face = entity->GetComponent<Texture>();

    resText = entity->FindAndGetComponent<Text>("Resilience", entity);
    luckText = entity->FindAndGetComponent<Text>("Luck", entity);
    speedText = entity->FindAndGetComponent<Text>("Speed", entity);

#ifndef OSSIUM_EDITOR
    UpdateAppearance();
#endif

}

void Explorer::UpdateAppearance(bool imageLoadFully)
{
    // Update character appearance
    auto resources = entity->GetService<ResourceController>();
    auto renderer = entity->GetService<Renderer>();

    if (face != nullptr)
    {
        face->SetSource(resources->Get<Image>(facePath, *renderer), imageLoadFully);
    }

    if (hat != nullptr)
    {
        hat->SetSource(resources->Get<Image>(hatPath, *renderer), imageLoadFully);
    }

    if (stache != nullptr)
    {
        stache->SetSource(resources->Get<Image>(stachePath, *renderer), imageLoadFully);
    }

    if (hair != nullptr)
    {
        hair->SetSource(resources->Get<Image>(hairPath, *renderer), imageLoadFully);
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
        luckText->text = Utilities::Format("Luck: {0}%", (int)(luck * 100.0f));
        luckText->dirty = true;
    }
}