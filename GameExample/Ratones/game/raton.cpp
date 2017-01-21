#include "raton.h"

Raton* Raton::instance = NULL;

void Raton::Update()
{
    transform.position.x = RF_Engine::instance->mouse.x;
    transform.position.y = RF_Engine::instance->mouse.y;

    if(RF_Engine::instance->mouse.z == 1)
    {
        OnClick = true;
        //RF_Engine::instance->mouse.z = 0;
    }
    else
    {
        OnClick = false;
    }
}

bool Raton::collision(RF_Process* p)
{
    Vector2<int> ppos1, ppos2, pscal1, pscal2;
    ppos1.x = p->transform.position.x; ppos1.y = p->transform.position.y;
    ppos2.x = transform.position.x; ppos2.y = transform.position.y;
    pscal2.x = 1; pscal2.y = 1;

    SDL_QueryTexture(p->graph,NULL,NULL,&pscal1.x,&pscal1.y);

    return RF_Engine::instance->collision(ppos1,pscal1,ppos2,pscal2);
}
void Ingame_Mouse::Update()
{
    transform.position.x = (RF_Engine::instance->mouse.x/10)*10;
    transform.position.y = (RF_Engine::instance->mouse.y/10)*10;

    if(RF_Engine::instance->mouse.z == 1)
    {
        OnClick = true;
        //RF_Engine::instance->mouse.z = 0;
    }
    else
    {
        OnClick = false;
    }
}
