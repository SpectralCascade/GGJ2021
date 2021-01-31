#ifndef ALLEVENTS_H
#define ALLEVENTS_H

#include <Ossium.h>

using namespace Ossium;

class GameController;

struct GameEventSchema : public Schema<GameEventSchema, 20>
{
    DECLARE_BASE_SCHEMA(GameEventSchema, 20);
    
    M(std::string, title);

    M(std::string, description);

    M(std::string, outcomeGood);

    M(std::string, outcomeBad);

    M(std::string, outcomeOther);

    M(std::string, yes) = "Yes";

    M(std::string, no) = "No";

    M(float, chanceGood) = 0.5f;
    
    M(float, chanceBad) = 0.5f;

    M(float, chanceOther) = 0.0f;

    M(int, terrainCondition) = 1 | 2 | 4 | 8 | 16;

};

class GameEvent : public GameEventSchema
{
public:
    CONSTRUCT_SCHEMA(SchemaRoot, GameEventSchema);

    GameEvent();

    bool CanFire(int terrainType);

    void Fire(GameController* gc);

    void Evaluate(GameController* gc);

    std::function<void()> outcomeGoodFunc;
    std::function<void()> outcomeBadFunc;
    std::function<void()> outcomeOtherFunc;

};

class EventSystem
{
public:
    void SetupEvents(GameController* game);

    std::vector<GameEvent> events;

};

#endif // ALLEVENTS_H
