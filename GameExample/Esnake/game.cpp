#include "game.h"
#include "mainprocess.h"

void Game::Start()
{
    RF_Engine::instance->Debug(type);

    bg = dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->bg;
    pL = new RF_Parallax_Layer();
        pL->getMirroring() = Vector2<int>(REPEAT,REPEAT);
        pL->size = Vector2<int>(bg->screen->w,bg->screen->h);
        pL->transform.position = Vector2<int>(0,0);
        pL->transform.scale = Vector2<float>(1.0f,1.0f);
        pL->transform.rotation = 0;

    for(i=0; i<bg->screen->w * bg->screen->h; i++)
    {
        pL->data.push_back(0x000000);
    }

    for(i = 0; i < 80; i++)
    {
        for(j = 0; j < 60; j++)
        {
            gamegrid[i][j] = 0;
        }
    }

    rectSize.x = bg->screen->w / 80;
    rectSize.y = bg->screen->h / 60;
    pL->drawAlone(bg);

    snake = Vector3<int>(40,30,3);
    snake_direction = 1;

    fC = 0;
    setFood();
}

void Game::Update()
{
    srand((int)RF_Engine::instance->time->currentTime);

    deltaCount += RF_Engine::instance->time->deltaTime;
    if(deltaCount >= 0.05f)
    {
        deltaCount = 0.0f;

        if(false == losed)
        {
            InputUpdate();
            SnakeUpdate();
            GridUpdate();
        }
        else
        {
            if(RF_Engine::instance->key[_return])
            {
                restart();
            }
        }

        handiCam();
        shakeCam();
        pL->drawAlone(bg);
    }
}

void Game::InputUpdate()
{
    if(RF_Engine::instance->key[_w] && snake_direction != 2){snake_direction = 0;}
    else if(RF_Engine::instance->key[_d] && snake_direction != 3){snake_direction = 1;}
    else if(RF_Engine::instance->key[_s] && snake_direction != 0){snake_direction = 2;}
    else if(RF_Engine::instance->key[_a] && snake_direction != 1){snake_direction = 3;}
}

void Game::SnakeUpdate()
{
    switch(snake_direction)
    {
        case 0:
            snake.y--;
            break;
        case 1:
            snake.x++;
            break;
        case 2:
            snake.y++;
            break;
        case 3:
            snake.x--;
            break;
    }

    if(snake.x >= 80){ snake.x = 0;}else if(snake.x < 0){ snake.x = 79;}
    if(snake.y >= 60){ snake.y = 0;}else if(snake.y < 0){ snake.y = 59;}

    if(gamegrid[snake.x][snake.y] == -1)
    {
        snake.z += 2;
        setFood();

        shake_x += 1;
    }
    if(gamegrid[snake.x][snake.y] < -1)
    {
        snake.z -= 5;

        shake_x = 0;
        shake_y = 0;
        effect_timer = -1;
    }
    if(gamegrid[snake.x][snake.y] > 0)
    {
        losed = true;
        dosTextos.x = RF_Engine::instance->write("You lose",{255,255,255},Vector2<int>((bg->screen->w>>1)-50, (bg->screen->h>>1)-50));
        dosTextos.y = RF_Engine::instance->write("[ENTER] para volver a intentarlo",{255,255,255},Vector2<int>((bg->screen->w>>1)-150, (bg->screen->h>>1)));
    }

    gamegrid[snake.x][snake.y] = snake.z;
}

void Game::GridUpdate()
{
    for(i = 0; i < 80; i++)
    {
        for(j = 0; j < 60; j++)
        {
            if(gamegrid[i][j] > 0){color = 0x0000FF;}
            else if(gamegrid[i][j] == -1){color = 0xFF0000;}
            else if(gamegrid[i][j] < -2){color = 0xFFFF00;}
            else{color = 0x000000;}

            if(gamegrid[i][j] > 0)
            {
                gamegrid[i][j]--;
            }
            if(gamegrid[i][j] < -2)
            {
                gamegrid[i][j]++;
            }
            if(gamegrid[i][j] == -2)
            {
                effect = 1 + rand()%effect_limit;
                RF_Engine::instance->Debug(effect);
                gamegrid[i][j] = 0;
            }

            drawRect();
        }
    }
}

void Game::setFood()
{
    color = 0x000001;
    do
    {
        i = rand()%80;
        j = rand()%60;
        color = gamegrid[i][j];
    }while(color != 0x000000);

    gamegrid[i][j] = -1;

    if(fC > 0)
    {
        if(fC%5 == 0)
        {
            color = 0x000001;
            do
            {
                i = rand()%80;
                j = rand()%60;
                color = gamegrid[i][j];
            }while(color != 0x000000);

            gamegrid[i][j] = -100;
        }
        else if(fC%3 == 0)
        {
            shake_y += 1;
        }
    }

    fC++;
}

void Game::shakeCam()
{
    if(shake_x > 0)
    {
        if(_shake_x < shake_x){_shake_x++;}
        if(_shake_y < shake_y){_shake_y++;}

        pL->transform.position.x += RF_Engine::instance->math->preCos(_shake_modifier*1000)*_shake_x;
        pL->transform.position.y += RF_Engine::instance->math->preSin(_shake_modifier*1000)*_shake_y;

        _shake_modifier += RF_Engine::instance->math->preCos(RF_Engine::instance->time->deltaTime);
    }
    else
    {
        if(_shake_x > 0)
        {
            _shake_x--;
        }
        if(_shake_y > 0)
        {
            _shake_y--;
        }
    }
}

void Game::handiCam()
{
    effect_timer -= RF_Engine::instance->time->deltaTime * 5;

    switch(effect)
    {
        case 1: //Escala
            effect_timer = 20.0f;
            pL->transform.scale.x = rand()%3 + 2;
            pL->transform.scale.y = rand()%3 + 2;

            effect = -1;
            break;

        case 2:
            effect_timer = 20.0f;

            pL->transform.scale.x = -1;
            pL->transform.scale.y = -1;

            effect = -1;
            break;

        case -1: //Esperamos a que termine el efecto
            if(effect_timer < 0)
            {
                pL->transform.scale.x = pL->transform.scale.y = 1;
                pL->transform.position = Vector2<int>(0,0);
                effect = 0;
            }
            break;
    }
}

void Game::drawRect()
{
    for(ii = i*rectSize.x; ii < (i+1)*rectSize.x; ii++)
    {
        for(jj = j*rectSize.y; jj < (j+1)*rectSize.y; jj++)
        {
            pL->data[bg->screen->w * jj + ii] = color;
        }
    }
}

void Game::restart()
{
    shake_x = 0;
    shake_y = 0;
    _shake_x = 0;
    _shake_y = 0;
    _shake_modifier = 200;
    effect = 0;
    losed = false;
    snake = Vector3<int>(40,30,3);
    snake_direction = 1;
    fC = 0;

    pL->getMirroring() = Vector2<int>(REPEAT,REPEAT);
    pL->size = Vector2<int>(bg->screen->w,bg->screen->h);
    pL->transform.position = Vector2<int>(0,0);
    pL->transform.scale = Vector2<float>(1.0f,1.0f);
    pL->transform.rotation = 0;

    for(i=0; i<bg->screen->w * bg->screen->h; i++)
    {
        pL->data.push_back(0x000000);
    }

    for(i = 0; i < 80; i++)
    {
        for(j = 0; j < 60; j++)
        {
            gamegrid[i][j] = 0;
        }
    }

    setFood();

    RF_Engine::instance->deleteText(dosTextos.x);
    RF_Engine::instance->deleteText(dosTextos.y);
}
