#include "GameController.h"

REGISTER_COMPONENT(GameController);

void GameController::OnCreate()
{
    auto resources = entity->GetService<ResourceController>();
}

void GameController::OnLoadFinish()
{
}
