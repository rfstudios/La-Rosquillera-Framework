#include "spawner.h"
#include "game.h"
#include "gameobjects/npc_mouse.h"

void Spawner::Start()
{
    graph = RF_Engine::instance->getGfx2D(("spawner_" + to_string(color)));
}

void Spawner::Update()
{
    deltaCount += RF_Engine::instance->time->deltaTime;
    if(deltaCount >= freq)
    {
        deltaCount = 0.0;

        if(Game::instance->population[color] < 10)
        {
            int r = RF_Engine::instance->newTask(new NPC_Mouse(color),id);
            RF_Engine::instance->taskManager[r]->transform.position = transform.position;
            Game::instance->population[color]++;
        }
    }
}
