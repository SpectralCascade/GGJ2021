#ifndef GameController_H
#define GameController_H

#include <Ossium.h>
#include "allevents.h"
#include "allnames.h"

using namespace Ossium;

class Explorer;
class MapView;
class EventPopup;

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

    // Update clock
    void Update();

    void UpdateText();

    void GoMainMenu();
    void GoNewGame();
    void GoQuit();
    void GoExplorerMenu();
    void GoMapView();

    void HireExplorer(Explorer* e);

    Entity* bottomBar = nullptr;
    Entity* explorerMenu = nullptr;
    Entity* mainMenu = nullptr;

    Button* hire1 = nullptr;
    Button* hire2 = nullptr;
    Button* hire3 = nullptr;

    VictorianNames* names = nullptr;

    EventPopup* popup;
    EventSystem* events;

    Clock clock;
    Timer gameTimer;
    Uint32 oldTime = 0;

    Rand* rng = nullptr;

    // Player money
    int funds = 200;

    MapView* mapView = nullptr;

    Text* fundsText = nullptr;

    Explorer* menuExplorers[3];
    Text* hireCosts[3];

    Button* exploreButton = nullptr;

    AudioMixer* mixer = nullptr;
    AudioBus* master = nullptr;

    AudioPlayer* footsteps = nullptr;

    GameEvent* toEvaluate = nullptr;

};

#endif // GameController_H
