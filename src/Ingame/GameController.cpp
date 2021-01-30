#include "GameController.h"

REGISTER_COMPONENT(GameController);

void GameController::OnCreate()
{
    mixer = new AudioMixer();
    master = mixer->InsertBus("Master");
    footsteps = new AudioPlayer();
    footsteps->Link(master);
    rng = new Rand();
}

void GameController::OnDestroy()
{
    delete footsteps;
    delete mixer;
}

void GameController::OnLoadFinish()
{
    exploreButton = entity->FindAndGetComponent<Button>("ExploreButton");
#ifndef OSSIUM_EDITOR
    if (exploreButton != nullptr)
    {
        exploreButton->OnClicked += [this] (auto& caller) {
            // TODO: play sound
            auto resources = entity->GetService<ResourceController>();
            footsteps->Play(resources->Get<AudioClip>("assets/Audio/Footsteps/FS_Medium05.wav"));
        };
    }
    for (unsigned int i = 0; i < 3; i++)
    {
        menuExplorers[i] = entity->FindAndGetComponent<Explorer>(Utilities::Format("{0}", i));
    }
#endif
}

void GameController::GenerateExplorers()
{
    if (menuExplorers[0] != nullptr)
    {
        // tier 1
        menuExplorers[0]->luck = rng.Float(0.0f, 0.04f);
    }
    if (menuExplorers[1] != nullptr)
    {
        // tier 2
        menuExplorers[1]->luck = rng.Float(0.02f, 0.07f);
    }
    if (menuExplorers[2] != nullptr)
    {
        // tier 3
        menuExplorers[2]->luck = rng.Float(0.06f, 0.1f);
    }
}
