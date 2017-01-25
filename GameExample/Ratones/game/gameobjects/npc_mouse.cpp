#include "gameobjects/npc_mouse.h"
#include "game.h"

void NPC_Mouse::Start()
{
    graph = RF_Engine::instance->getGfx2D(("mouse_" + to_string(color)));
    speed = Game::instance->mouseSpeed;
}

void NPC_Mouse::Update()
{
    //Control de cuándo cae y cuándo no
        Vector2<int>posVer = Vector2<int>((int)transform.position.x,(int)transform.position.y);
        if(direction == DIR_LEFT)
        {
            posVer.x +=10;
        }

        if( Game::instance->Plataformas[posVer.x/10][(posVer.y + 10)/10] != 0)
        {
            on_place = true;
        }
        else
        {
            on_place = false;
        }

    //Control de giro
        if(direction == DIR_LEFT && on_place)
        {
            if(Game::instance->Plataformas[((int)transform.position.x - 1)/10][(int)transform.position.y/10] > 0 &&
              (Game::instance->Plataformas[((int)transform.position.x - 1)/10][(int)transform.position.y/10] < 100 ||
               Game::instance->Plataformas[((int)transform.position.x - 1)/10][(int)transform.position.y/10] > 103))
            {
                direction = DIR_RIGHT;
            }
        }
        else if(direction == DIR_RIGHT && on_place)
        {
            if(Game::instance->Plataformas[((int)transform.position.x + 10)/10][(int)transform.position.y/10] > 0  > 0 &&
              (Game::instance->Plataformas[((int)transform.position.x + 10)/10][(int)transform.position.y/10] < 100 ||
               Game::instance->Plataformas[((int)transform.position.x + 10)/10][(int)transform.position.y/10] > 103))
            {
                direction = DIR_LEFT;
            }
        }

    if(!on_place)
    {
        transform.position.y += speed.y * RF_Engine::instance->time->deltaTime;

        if((int)transform.position.y % 10 != 0)
        {
            if(direction == DIR_RIGHT)
            {
                transform.position.x = (((int)transform.position.x) / 10) * 10;
            }
            else
            {
                transform.position.x = (((int)transform.position.x + 10) / 10) * 10;
            }
        }

        if(transform.position.y > RF_Engine::instance->ventana->height() + 10)
        {
            signal = S_KILL;
            Game::instance->population[color]--;
        }
    }
    else
    {
        if(speed.x > 0)
        {
            transform.position.y = ((int)transform.position.y / 10) * 10;
        }

        if(direction == DIR_RIGHT)
        {
            transform.position.x += speed.x * RF_Engine::instance->time->deltaTime;
        }
        else
        {
            transform.position.x -= speed.x * RF_Engine::instance->time->deltaTime;
        }

        if(transform.position.x > RF_Engine::instance->ventana->width() - 10)
        {
            transform.position.x = 0;
        }
        else if(transform.position.x < 0)
        {
            transform.position.x = RF_Engine::instance->ventana->width() - 10;
        }
    }
}
