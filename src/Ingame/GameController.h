#ifndef GameController_H
#define GameController_H

#include <Ossium.h>
#include "explorer.h"

using namespace Ossium;

class MissionOverview;

/// The "hub" class that game-specific bits can access everything via.
class GameController : public Component
{
public:
    DECLARE_COMPONENT(Component, GameController);

    // Initialise schemas
    void OnCreate();

    void OnDestroy();

    // Setup the game scene.
    void OnLoadFinish();

    // Generates the explorer characters.
    void GenerateExplorers();

    Rand* rng = nullptr;

    // Player money
    int funds = 200;

    Explorer* menuExplorers[3];

    Explorer* hiredExplorer = nullptr;

    Button* exploreButton = nullptr;

    AudioMixer* mixer = nullptr;
    AudioBus* master = nullptr;

    AudioPlayer* footsteps = nullptr;

};

#endif // GameController_H
