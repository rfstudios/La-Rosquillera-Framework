#include "madriguera.h"
#include "game.h"
#include "gameobjects/npc_mouse.h"
#include "rf_engine.h"

void Madriguera::Start()
{
    graph = RF_Engine::instance->getGfx2D(("madriguera_" + to_string(color)));
}

void Madriguera::Update()
{
    NPC_Mouse* col = dynamic_cast<NPC_Mouse*>(RF_Engine::instance->collision("NPC_Raton", this));
    if(col)
    {
        if(col->Color() == color)
        {
            RF_Engine::instance->sendSignal(col->id,S_KILL);
            Game::instance->population[color]--;
            Game::instance->SetPoint(color);
        }
    }
}
