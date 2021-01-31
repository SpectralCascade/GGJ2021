#include "allevents.h"
#include "eventpopup.h"
#include "GameController.h"
#include "terrain.h"

GameEvent::GameEvent()
{
    outcomeGoodFunc = [] () {};
    outcomeBadFunc = [] () {};
    outcomeOtherFunc = [] () {};
}

void GameEvent::Evaluate(bool decision, GameController* gc)
{
    if (decision)
    {
        float maxValue = chanceGood + chanceBad + chanceOther;
        float chance = gc->rng->Float(0.0f, maxValue);

        if (chance <= chanceGood)
        {
            gc->popup->Show("Good News!", outcomeGood, "X", outcomeGoodFunc);
        }
        else if (chance <= chanceGood + chanceBad)
        {
            gc->popup->Show("Bad News...", outcomeBad, "X", outcomeBadFunc);
        }
        else
        {
            gc->popup->Show("", outcomeOther, "X", outcomeOtherFunc);
        }
    }
}

void EventSystem::SetupEvents(GameController* game)
{

    GameEvent event;

    // Copy and paste this template and fill in words between the "" double quotes where applicable (can leave outcomeOther blank if no other outcome).
    // The chances are percentages where 0.5f = 50%, 0.25f = 25% and so on; higher percentage = higher chance of occurring.
    // You can remove terrain types from event.terrainCondition to specify which terrain the event can happen on,
    // for instance to make sure the event only fires for plains and hills, do: event.terrainCondition = TERRAIN_PLAIN | TERRAIN_HILL;

    // START OF EVENT TEMPLATE

    event = GameEvent();

    event.title = "";
    event.description = "";
    event.outcomeGood = "";
    event.outcomeBad = "";
    event.outcomeOther = "";
    event.yes = "Yes";
    event.no = "No";

    event.chanceGood = 0.8f;
    event.chanceBad = 0.2f;
    event.chanceOther = 0.0f;

    event.terrainCondition = TERRAIN_PLAIN | TERRAIN_MOUNTAIN | TERRAIN_LAKE | TERRAIN_HILL | TERRAIN_FOREST;

    event.outcomeGoodFunc = [&] () {};
    event.outcomeBadFunc = [&] () {};
    event.outcomeOtherFunc = [&] () {};

    events.push_back(event);

    // END OF EVENT TEMPLATE

}
