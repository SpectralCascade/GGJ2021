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

bool GameEvent::CanFire(int terrainType)
{
    return terrainType & terrainCondition;
}

void GameEvent::Fire(GameController* gc)
{
    gc->popup->Show(
        title,
        description,
        yes,
        [&, gc] () {
            gc->toEvaluate = this;
            gc->popup->Hide();
        },
        no,
        [] () {
            // Do nothing
        }
    );
}

void GameEvent::Evaluate(GameController* gc)
{
    float maxValue = chanceGood + chanceBad + chanceOther;
    float chance = gc->rng->Float(0.0f, maxValue);
    if (chance <= chanceGood)
    {
        outcomeGoodFunc();
        gc->popup->Show("Good News!", outcomeGood, "X", [] () {});
    }
    else if (chance <= chanceGood + chanceBad)
    {
        outcomeBadFunc();
        gc->popup->Show("Bad News...", outcomeBad, "X", [] () {});
    }
    else
    {
        outcomeOtherFunc();
        gc->popup->Show("", outcomeOther, "X", [] () {});
    }
}

void EventSystem::SetupEvents(GameController* game)
{

    GameEvent event;

    // Copy and paste this template and fill in words between the "" double quotes where applicable (can leave outcomeOther blank if no other outcome).
    // The chances are percentages where 0.5f = 50%, 0.25f = 25% and so on; higher percentage = higher chance of occurring.
    // You can remove terrain types from event.terrainCondition to specify which terrain the event can happen on,
    // for instance to make sure the event only fires for plains and hills, do: event.terrainCondition = TERRAIN_PLAIN | TERRAIN_HILL;

    /*
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
    */
    
    event = GameEvent();
    
    event.title = "The Cave";
    event.description = "I have found a vast open cave.  Would you like me to explore it?";
    event.outcomeGood = " I’ve walked in and found some gold.";
    event.outcomeBad = "There was nothing of value.";
    event.outcomeOther = "Your explorer walked into the cave and the entrance collapsed behind them sealing them inside the dark cave.";
    event.yes = "Yes";
    event.no = "No";

    event.chanceGood = 0.8f;
    event.chanceBad = 0.2f;
    event.chanceOther = 0.0f;
    
    event.terrainCondition = TERRAIN_PLAIN | TERRAIN_MOUNTAIN | TERRAIN_HILL;

    event.outcomeGoodFunc = [&] () {};
    event.outcomeBadFunc = [&] () {};
    event.outcomeOtherFunc = [&] () {};

    events.push_back(event);
    
    
    
    event = GameEvent();

    event.title = "The rustling bushes";
    event.description = "I’ve started to hear rustling in the bushes and I’m unsure what might have caused it.  Would you like me to continue?";
    event.outcomeGood = "There was nothing around it must have been the wind.";
    event.outcomeBad = "We were attacked by bandits and they stole some equipment";
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
    
    
    
    event = GameEvent();

    event.title = "Shine in the distance";
    event.description = "In the distance I can see a shiny object, would you like me to continue searching?";
    event.outcomeGood = "I found some gold on the floor.";
    event.outcomeBad = "I found some silver and was attacked by magpies, they really wanted that silver.";
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
    
    
    
    
    event = GameEvent();

    event.title = "The lost treasure?";
    event.description = "I was told there might be some lost treasure hidden in this mountain (or was it the other one?)  Would you like me to explore the area?";
    event.outcomeGood = "I’ve found a small chest hidden away with some gold";
    event.outcomeBad = "It was the wrong mountain there is nothing here";
    event.outcomeOther = "There was no treasure and now there’s no way for your explorer to get back down safely ";
    event.yes = "Yes";
    event.no = "No";

    event.chanceGood = 0.8f;
    event.chanceBad = 0.2f;
    event.chanceOther = 0.1f;

    event.terrainCondition =  TERRAIN_MOUNTAIN;

    event.outcomeGoodFunc = [&] () {};
    event.outcomeBadFunc = [&] () {};
    event.outcomeOtherFunc = [&] () {};

    events.push_back(event);
    
    
    
    event = GameEvent();

    event.title = "The wolf's den";
    event.description = "In the distance I can hear the howling of what seems to be a wolf.  Would you like me to proceed?";
    event.outcomeGood = "I have managed to avoid the wolf.";
    event.outcomeBad = "I’ve been spotted by the wolf and have been led astray from the path.";
    event.outcomeOther = "";
    event.yes = "Yes";
    event.no = "No";

    event.chanceGood = 0.8f;
    event.chanceBad = 0.2f;
    event.chanceOther = 0.0f;

    event.terrainCondition = TERRAIN_LAKE | TERRAIN_HILL | TERRAIN_FOREST;

    event.outcomeGoodFunc = [&] () {};
    event.outcomeBadFunc = [&] () {};
    event.outcomeOtherFunc = [&] () {};

    events.push_back(event);
    
    
    
    event = GameEvent();

    event.title = "A grizzly encounter";
    event.description = "I can hear the roar of a ferocious bear, would you like me to push on?";
    event.outcomeGood = "The bear walked away, something else must have gotten it’s attention.";
    event.outcomeBad = "The bear was faster than I thought, thankfully I managed to escape.";
    event.outcomeOther = "";
    event.yes = "Yes";
    event.no = "No";

    event.chanceGood = 0.8f;
    event.chanceBad = 0.2f;
    event.chanceOther = 0.0f;

    event.terrainCondition = TERRAIN_MOUNTAIN | TERRAIN_LAKE | TERRAIN_HILL | TERRAIN_FOREST;

    event.outcomeGoodFunc = [&] () {};
    event.outcomeBadFunc = [&] () {};
    event.outcomeOtherFunc = [&] () {};

    events.push_back(event);
    
    
    
    event = GameEvent();

    event.title = "A dangerous path";
    event.description = "I've come to a crossroads, the path I was following began to look dangerous, but there seems to be a safer path.  Would you like to proceed down the safer looking path?";
    event.outcomeGood = "The pathway took me around safely, I’ll mark it on the map";
    event.outcomeBad = "The path lead to a marsh, the journey destroyed some supplies";
    event.outcomeOther = "";
    event.yes = "Yes";
    event.no = "No";

    event.chanceGood = 0.8f;
    event.chanceBad = 0.2f;
    event.chanceOther = 0.0f;

    event.terrainCondition = TERRAIN_MOUNTAIN | TERRAIN_HILL | TERRAIN_FOREST;

    event.outcomeGoodFunc = [&] () {};
    event.outcomeBadFunc = [&] () {};
    event.outcomeOtherFunc = [&] () {};

    events.push_back(event);
    
    
    
    event = GameEvent();

    event.title = "Wild berries";
    event.description = "I’m starving and I’ve found a bush of wild berries, which look potentially safe to eat.  Can I eat some berries so I can continue my task at full efficiency?";
    event.outcomeGood = "I feel great and i’m ready to continue ";
    event.outcomeBad = "The berries tasted horrible and I’m still hungry";
    event.outcomeOther = "The berries were poisonous knocking your explorer out on the spot";
    event.yes = "Yes";
    event.no = "No";

    event.chanceGood = 0.8f;
    event.chanceBad = 0.2f;
    event.chanceOther = 0.1f;

    event.terrainCondition = TERRAIN_PLAIN | TERRAIN_MOUNTAIN | TERRAIN_LAKE | TERRAIN_HILL | TERRAIN_FOREST;

    event.outcomeGoodFunc = [&] () {};
    event.outcomeBadFunc = [&] () {};
    event.outcomeOtherFunc = [&] () {};

    events.push_back(event);
    
    
    event = GameEvent();

    event.title = "The slepy explorer";
    event.description = "I’m exhausted, may I rest for a little while?";
    event.outcomeGood = "I rested up and can continue";
    event.outcomeBad = "Whilst I was sleeping someone stole our equipment";
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
    
    
    
    event = GameEvent();

    event.title = "The lake";
    event.description = "I’ve found a lake but it seems it’ll take a long time for me to get around, I can attempt to swim across.  Would you like to swim across?";
    event.outcomeGood = "I successfully swam across the lake";
    event.outcomeBad = "I attempted to swim across and was bitten by an adder, I decided to swim back to avoid any more trouble";
    event.outcomeOther = "Your explorer didn’t know how to actually swim and drowned in the process";
    event.yes = "Yes";
    event.no = "No";

    event.chanceGood = 0.8f;
    event.chanceBad = 0.2f;
    event.chanceOther = 0.1f;

    event.terrainCondition = TERRAIN_LAKE;

    event.outcomeGoodFunc = [&] () {};
    event.outcomeBadFunc = [&] () {};
    event.outcomeOtherFunc = [&] () {};

    events.push_back(event);
    
    
    
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
    
    
    event = GameEvent();

    event.title = "A leap of faith";
    event.description = "My path is blocked but it seems there might be a way to jump down.  Would you like me to jump down?";
    event.outcomeGood = "The height was much smaller than what I perceived.";
    event.outcomeBad = "The height was a bit too much for my ankles.  I might need to take a break.";
    event.outcomeOther = "Your explorer underestimated the drop and plummeted to their death. ";
    event.yes = "Yes";
    event.no = "No";

    event.chanceGood = 0.8f;
    event.chanceBad = 0.2f;
    event.chanceOther = 0.1f;

    event.terrainCondition = TERRAIN_MOUNTAIN | TERRAIN_HILL;

    event.outcomeGoodFunc = [&] () {};
    event.outcomeBadFunc = [&] () {};
    event.outcomeOtherFunc = [&] () {};

    events.push_back(event);
    
    
    event = GameEvent();

    event.title = "The dark forest";
    event.description = "I’ve come across a dense forest, I might be able to save time if I walk through it.  Would you like me to attempt to save time?";
    event.outcomeGood = "The forest was much shorter than I expected and I managed to clear a path.";
    event.outcomeBad = "I’ve been lost for hours, I really need a rest.";
    event.outcomeOther = "";
    event.yes = "Yes";
    event.no = "No";

    event.chanceGood = 0.8f;
    event.chanceBad = 0.2f;
    event.chanceOther = 0.0f;

    event.terrainCondition = TERRAIN_FOREST;

    event.outcomeGoodFunc = [&] () {};
    event.outcomeBadFunc = [&] () {};
    event.outcomeOtherFunc = [&] () {};

    events.push_back(event);
    
    
    event = GameEvent();

    event.title = "The dangerous path";
    event.description = "The path you’ve sent me down looks dangerously unstable, I can still turn back.  Would you like me to continue down the original path?";
    event.outcomeGood = "The path was much more stable than it looked";
    event.outcomeBad = "The pathway broke after putting one foot down so I went down the safe path";
    event.outcomeOther = "The patch collapsed and took your explorer with it";
    event.yes = "Yes";
    event.no = "No";

    event.chanceGood = 0.8f;
    event.chanceBad = 0.2f;
    event.chanceOther = 0.1f;

    event.terrainCondition = TERRAIN_MOUNTAIN;

    event.outcomeGoodFunc = [&] () {};
    event.outcomeBadFunc = [&] () {};
    event.outcomeOtherFunc = [&] () {};

    events.push_back(event);
    
    
    event = GameEvent();

    event.title = "Thirsty work";
    event.description = "I’ve been walking for hours and have run out of water, I think I can see a river in the distance.  Can I go off the path to fill up my flask?";
    event.outcomeGood = "You managed to find water and fill up your flask.";
    event.outcomeBad = "The water river you saw must have been a trick your eyes played on you.";
    event.outcomeOther = "Your explorer couldn’t find a water source and passed out from dehydration.";
    event.yes = "Yes";
    event.no = "No";

    event.chanceGood = 0.8f;
    event.chanceBad = 0.2f;
    event.chanceOther = 0.1f;

    event.terrainCondition = TERRAIN_PLAIN | TERRAIN_LAKE;

    event.outcomeGoodFunc = [&] () {};
    event.outcomeBadFunc = [&] () {};
    event.outcomeOtherFunc = [&] () {};

    events.push_back(event);
    
    
    event = GameEvent();

    event.title = "A cry for help";
    event.description = "I can hear a cry for help in the distance, they might be in danger.  Would you like me to help?";
    event.outcomeGood = "I helped the people in distress and they rewarded me with some gold.";
    event.outcomeBad = "It was a trap and they stole some gold ";
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
    
    
    event = GameEvent();

    event.title = "A strange encounter";
    event.description = "A strange man has approached me asking for help, I’m not sure about this character.  Would you still like me to help him with his troubles?";
    event.outcomeGood = "I assisted the man and he gave me a payment of gold";
    event.outcomeBad = "He dragged me off the path and left me stranded, I’m fatigued from trying to find the path again.";
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
    
}
