#include "GameController.h"
#include "explorer.h"
#include "mapview.h"
#include "eventpopup.h"

REGISTER_COMPONENT(GameController);

void GameController::OnCreate()
{
    mixer = new AudioMixer();
    master = mixer->InsertBus("Master");
    footsteps = new AudioPlayer();
    footsteps->Link(master);
    music = new AudioPlayer();
    music->Link(master);
    rng = new Rand();
    names = new VictorianNames();
}

void GameController::OnDestroy()
{
    delete footsteps;
    delete mixer;
}

void GameController::OnLoadFinish()
{
    entity->GetService<Renderer>()->SetBackgroundColor(Color(150, 64, 0));

    exploreButton = entity->FindAndGetComponent<Button>("ExploreButton");
    popup = entity->FindAndGetComponent<EventPopup>("EventPopup");
    explorerMenu = entity->Find("ExplorerMenu");
    bottomBar = entity->Find("BottomBarMAIN");
    mainMenu = entity->Find("MainMenu");

    hire1 = entity->FindAndGetComponent<Button>("Hire1");
    hire2 = entity->FindAndGetComponent<Button>("Hire2");
    hire3 = entity->FindAndGetComponent<Button>("Hire3");

#ifndef OSSIUM_EDITOR
    bottomBar->SetActive(false);
    explorerMenu->SetActive(false);

    auto resources = entity->GetService<ResourceController>();
    music->Play(resources->Get<AudioClip>("assets/Audio/Music/menu.wav"), 0.5f);

    if (hire1 != nullptr)
    {
        hire1->OnClicked += [&] (Button& caller) {
            HireExplorer(menuExplorers[0]);
        };
    }
    if (hire2 != nullptr)
    {
        hire2->OnClicked += [&] (Button& caller) {
            HireExplorer(menuExplorers[1]);
        };
    }
    if (hire3 != nullptr)
    {
        hire3->OnClicked += [&] (Button& caller) {
            HireExplorer(menuExplorers[2]);
        };
    }

    mapView = entity->FindAndGetComponent<MapView>("MapView");

    if (exploreButton != nullptr)
    {
        exploreButton->OnClicked += [this] (auto& caller) {
            auto resources = entity->GetService<ResourceController>();
            footsteps->Play(resources->Get<AudioClip>("assets/Audio/Footsteps/FS_Medium05.wav"));
        };
    }
    for (unsigned int i = 0; i < 3; i++)
    {
        menuExplorers[i] = entity->FindAndGetComponent<Explorer>(Utilities::Format("{0}", i + 1));
        explorerNames[i] = entity->FindAndGetComponent<Text>("Name", menuExplorers[i]->GetEntity());
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

    events = new EventSystem();
    events->SetupEvents(this);

    Button* playButton = mainMenu->FindAndGetComponent<Button>("PlayButton");
    Button* quitButton = mainMenu->FindAndGetComponent<Button>("QuitButton");
    if (playButton != nullptr)
    {
        playButton->OnClicked += [&] (Button& caller) {
            GoNewGame();
        };
    }
    if (quitButton != nullptr)
    {
        quitButton->OnClicked += [&] (Button& caller) {
            GoQuit();
        };
    }

#endif
}

void GameController::Update()
{
    Uint32 nowTime = gameTimer.GetTicks();
    clock.Update((float)(nowTime - oldTime) / 1000.0f);
    oldTime = nowTime;

    if (toEvaluate != nullptr)
    {
        toEvaluate->Evaluate(this);
        toEvaluate = nullptr;
    }
}

void GameController::UpdateText()
{
    if (fundsText != nullptr)
    {
        fundsText->text = Utilities::Format("Funds: ${0}", funds);
        fundsText->dirty = true;
    }
}

void GameController::GenerateExplorers()
{
    if (menuExplorers[0] != nullptr)
    {
        // tier 1
        menuExplorers[0]->luck = (float)rng->Int(0, 4) * 0.01f;
    }
    if (menuExplorers[1] != nullptr)
    {
        // tier 2
        menuExplorers[1]->luck = (float)rng->Int(2, 7) * 0.01f;
    }
    if (menuExplorers[2] != nullptr)
    {
        // tier 3
        menuExplorers[2]->luck = (float)rng->Int(6, 10) * 0.01f;
    }

    // Applies to all
    for (unsigned int i = 0; i < 3; i++)
    {
        menuExplorers[i]->name = Utilities::Format("{0} {1}", *PickRandom(names->firstNames), *PickRandom(names->lastNames));
        menuExplorers[i]->cost = (menuExplorers[i]->tier + 1) * 10;
        int face = rng->Int(1, 6);
        menuExplorers[i]->facePath = Utilities::Format("assets/Sprites/Characters/Head_{0}.png", face);
        menuExplorers[i]->hatPath = Utilities::Format("assets/Sprites/Characters/Hat_{0}.png", menuExplorers[i]->tier + 1);
        int accessory = rng->Int(1, 7);
        menuExplorers[i]->stachePath = Utilities::Format(
            "assets/Sprites/Characters/Accessory_{0}{1}.png",
            accessory, 
            accessory == 1 && face == 2 ? "_2" : (accessory == 4 && (face == 2 || face == 3) ? "_2_3" : "")
        );

        menuExplorers[i]->UpdateAppearance();
        explorerNames[i]->text = menuExplorers[i]->name;
        explorerNames[i]->dirty = true;
    }
}

void GameController::GoMainMenu()
{
    mainMenu->SetActive(true);
    auto resources = entity->GetService<ResourceController>();
    music->Play(resources->Get<AudioClip>("assets/Audio/Music/menu.wav"), 0.5f);
}

void GameController::GoNewGame()
{
    GoExplorerMenu();
}

void GameController::GoQuit()
{
    // TODO
}

void GameController::GoExplorerMenu()
{
    mainMenu->SetActive(false);
    bottomBar->SetActive(false);
    mapView->GetEntity()->SetActive(false);
    explorerMenu->SetActive(true);
}

void GameController::GoMapView()
{
    auto resources = entity->GetService<ResourceController>();
    music->Play(resources->Get<AudioClip>("assets/Audio/Music/bgm.wav"), 0.5f);
    mainMenu->SetActive(false);
    explorerMenu->SetActive(false);
    bottomBar->SetActive(true);
    mapView->GetEntity()->SetActive(true);
    mapView->UpdateText();
}

void GameController::HireExplorer(Explorer* e)
{
    auto resources = entity->GetService<ResourceController>();
    footsteps->Play(resources->Get<AudioClip>(Utilities::Format("assets/Audio/Wilhelm/Screams/Shock_Scream-00{0}.wav", rng->Int(1, 6))));

    GoMapView();

    mapView->GenerateMap();
    // TODO: remove me, should only spawn on map load from hiring menu
    mapView->SpawnExplorer(e);
}
