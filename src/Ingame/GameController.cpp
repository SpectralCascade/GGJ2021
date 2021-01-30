#include "GameController.h"
#include "explorer.h"

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
            auto resources = entity->GetService<ResourceController>();
            footsteps->Play(resources->Get<AudioClip>("assets/Audio/Footsteps/FS_Medium05.wav"));
        };
    }
    for (unsigned int i = 0; i < 3; i++)
    {
        menuExplorers[i] = entity->FindAndGetComponent<Explorer>(Utilities::Format("{0}", i));
        if (menuExplorers[i] != nullptr)
        {
            hireCosts[i] = entity->FindAndGetComponent<Text>("Cost", menuExplorers[i]->GetEntity());
            if (hireCosts[i] != nullptr)
            {
                hireCosts[i]->text = Utilities::Format("Cost: ${0}", menuExplorers[i]->cost);
                hireCosts[i]->dirty = true;
            }
        }
    }

    // On first load, generate a batch of explorers
    GenerateExplorers();

    fundsText = entity->FindAndGetComponent<Text>("Funds");
    if (fundsText != nullptr)
    {
        fundsText->text = Utilities::Format("Funds: ${0}", funds);
        fundsText->dirty = true;
    }
#endif
}

void GameController::GenerateExplorers()
{
    if (menuExplorers[0] != nullptr)
    {
        // tier 1
        menuExplorers[0]->luck = rng->Float(0.0f, 0.04f);
    }
    if (menuExplorers[1] != nullptr)
    {
        // tier 2
        menuExplorers[1]->luck = rng->Float(0.02f, 0.07f);
    }
    if (menuExplorers[2] != nullptr)
    {
        // tier 3
        menuExplorers[2]->luck = rng->Float(0.06f, 0.1f);
    }

    // Applies to all
    for (unsigned int i = 0; i < 3; i++)
    {
        // TODO: Randomise name and character appearance
    }
}
