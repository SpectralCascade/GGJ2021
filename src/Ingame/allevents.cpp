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
            popup->Show("Good News!", outcomeGood, "X", outcomeGoodFunc);
        }
        else if (chance <= chanceGood + chanceBad)
        {
            popup->Show("Bad News...", outcomeBad, "X", outcomeBadFunc);
        }
        else
        {
            popup->Show("", outcomeOther, "X", outcomeOtherFunc);
        }
    }
}

void SetupEvents(GameController* game)
{

    GameEvent event;

    // Copy and paste this template and fill in words between the "" double quotes.
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

    // Tim TODO; will put outcome logic in here.
    event.outcomeGoodFunc = [&] () {};
    event.outcomeBadFunc = [&] () {};
    event.outcomeOtherFunc = [&] () {};

    events.push_back(event);

    // END OF EVENT TEMPLATE

}
