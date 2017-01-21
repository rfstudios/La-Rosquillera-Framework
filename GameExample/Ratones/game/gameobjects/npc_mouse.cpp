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
        if(direction == DIR_LEFT)
        {
            if(Game::instance->Plataformas[((int)transform.position.x)/10][(int)transform.position.y/10] > 0 &&
              (Game::instance->Plataformas[((int)transform.position.x)/10][(int)transform.position.y/10] < 100 ||
               Game::instance->Plataformas[((int)transform.position.x)/10][(int)transform.position.y/10] > 103))
            {
                direction = DIR_RIGHT;
            }
        }
        else
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
        transform.position.y += speed.y;

        if(transform.position.y > RF_Engine::instance->ventana->height() + 10)
        {
            transform.position.y = -10;
        }
    }
    else
    {
        if(direction == DIR_RIGHT)
        {
            transform.position.x += speed.x;
        }
        else
        {
            transform.position.x -= speed.x;
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
