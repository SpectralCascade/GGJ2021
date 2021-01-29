#ifndef GameController_H
#define GameController_H

#include <Ossium.h>

using namespace Ossium;

class MissionOverview;

/// The "hub" class that game-specific bits can access everything via.
class GameController : public Component
{
public:
    DECLARE_COMPONENT(Component, GameController);

    // Initialise schemas
    void OnCreate();

    // Setup the game scene.
    void OnLoadFinish();

    // Player money
    int funds = 200;

};

#endif // GameController_H
