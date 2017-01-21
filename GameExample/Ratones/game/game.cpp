#include "game.h"
#include "mainprocess.h"
#include "raton.h"

#include "gameobjects/tool_gui.h"
#include "gameobjects/spawner.h"
#include "gameobjects/madriguera.h"
#include "gameobjects/dureza.h"
#include "gameobjects/splitter.h"
#include "gameobjects/elevator.h"
#include "gameobjects/colorchanger.h"
#include "gameobjects/floor_splitter.h"

#include "test.h"

Game* Game::instance = NULL;

void Game::Start()
{
    Raton::instance->graph = RF_Engine::instance->getGfx2D("plataforma");
    callLevel(lvl);
}

void Game::Update()
{
    if(gameStatus == 0)
    {
        if(checkVictory())
        {
            gameStatus = 1;
        }

        if(!pressed)
        {
            if(RF_Engine::instance->key[_space])
            {
                pressed = true;
                ChangeTool();
            }
            if(RF_Engine::instance->key[_return])
            {
                pressed = true;
                gameStatus = 1;
                lvl--;
            }

            if(Raton::instance->OnClick)
            {
                if(tools_available[selectedTool] > 0 || tools_available[selectedTool] <= -1)
                {
                    RF_Process* aux = RF_Engine::instance->collision("node",Raton::instance);
                    if(aux)
                    {
                        RF_Engine::instance->sendSignal(aux->id,S_KILL_TREE);
                    }

                    PlaceNode(selectedTool,Vector2<int>((int)Raton::instance->transform.position.x/10,(int)Raton::instance->transform.position.y/10));
                    tools_available[selectedTool]--;
                }
                pressed = true;
            }
        }
        else
        {
            if(!RF_Engine::instance->key[_space] && !Raton::instance->OnClick && !RF_Engine::instance->key[_return])
            {
                pressed = false;
            }
        }
    }
    else if(gameStatus == 1)
    {
        if(pressed)
        {
            if(!RF_Engine::instance->key[_return] && !Raton::instance->OnClick)
            {
                pressed = false;
            }
            else
            {
                return;
            }
        }

        borra_todo();
        gameStatus = 2;
    }
    else if(gameStatus == 2)
    {
        lvl++;
        callLevel(lvl);
    }
}

void Game::parseLevel()
{
    for(unsigned int i = 0; i < 64; i++)
    {
        for(unsigned int j = 0; j < 48; j++)
        {
            PlaceNode(Plataformas[i][j], Vector2<int>(i,j));
        }
    }

    int p = 0, aux;
    for(int i = 0; i < 6; i++)
    {
        if(tools_available[i] > 0 || tools_available[i] == -1)
        {
            aux = RF_Engine::instance->newTask(new tool_gui(i, Vector2<float>(580.0, 20.0 + (p*20.0))), id);
            p++;
        }
    }
}

void Game::PlaceNode(int node, Vector2<int> pos)
{
    Plataformas[pos.x][pos.y] = node;
    if(node == 0){return;}

    int aux_id;

    if(node == 1)
    {
        aux_id = RF_Engine::instance->newTask(new dureza(),Game::instance->id);
    }
    else if(node >= SPAWN_RED + 100 && node <= SPAWN_BLUE + 100)
    {
        aux_id = RF_Engine::instance->newTask(new Madriguera(node - 100), Game::instance->id);
        scores.push_back(Score(0, vict[node - 100],node - 100,Vector2<int>(5,30*scores.size()+5)));
    }
    else if(node == 2)
    {
        aux_id = RF_Engine::instance->newTask(new Splitter(),Game::instance->id);
    }
    else if(node == 3)
    {
        aux_id = RF_Engine::instance->newTask(new Elevator(),Game::instance->id);
    }
    else if(node == 4)
    {
        aux_id = RF_Engine::instance->newTask(new ColorChanger(),Game::instance->id);
    }
    else if(node == 5)
    {
        aux_id = RF_Engine::instance->newTask(new Floor_Splitter(),Game::instance->id);
    }

    RF_Engine::instance->taskManager[aux_id]->transform.position = Vector2<float>(pos.x*10,pos.y*10);

}

void Game::SetPoint(int col)
{
    for(unsigned int i = 0; i < scores.size(); i++)
    {
        if(scores[i].color == col)
        {
            scores[i].value++;
            scores[i].Refresh();
        }
    }
}

void Game::ChangeTool()
{
    int go = 0;
    do
    {
        selectedTool++;
        go++;
        if(selectedTool > 5){selectedTool = 0;}
    }while(tools_available[selectedTool] == 0 && go <= 7);

    string toolname;
    switch(selectedTool)
    {
        case 0:
            toolname = "mouse2";
            break;
        case 1:
            toolname = "plataforma";
            break;
        case 2:
            toolname = "splitter";
            break;
        case 3:
            toolname = "elevator";
            break;
        case 4:
            toolname = "colorchanger";
            break;
        case 5:
            toolname = "floor_splitter";
            break;
    }

    if(go <= 7)
    {
        Raton::instance->graph = RF_Engine::instance->getGfx2D(toolname);
    }
    else
    {
        Raton::instance->graph = NULL;
    }
}

bool Game::checkVictory()
{
    for(unsigned int i = 0; i < scores.size(); i++)
    {
        if(scores[i].value < scores[i].victory)
        {
            return false;
        }
    }

    return true;
}

void Game::callLevel(int l)
{
    vict[0] = vict[1] = vict[2] = vict[3] = 0;
    population[0] = population[1] = population[2] = population[3] = 0;
    scores.clear();
    RF_Engine::instance->deleteText(-1);

    for(int i = 0; i < 6; i++)
    {
        tools_available[i] = 0;
    }

    switch(l)
    {
        case 1:
            Levels::Level1();
            break;
        case 2:
            Levels::Level2();
            break;
        case 3:
            Levels::Level3();
            break;
        case 4:
            Levels::Level4();
            break;
        case 5:
            Levels::Level20();
            break;

        default:
            borra_todo();
            dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->state() = 3;
            break;
    }

    parseLevel();

    gameStatus = 0;

    //Resetea la tool
        selectedTool = 5;
        ChangeTool();
}

void Game::borra_todo()
{
    unsigned int siz = RF_Engine::instance->taskManager.size();
    for(unsigned int i = 0; i < siz; i++)
    {
        if(RF_Engine::instance->taskManager[i] != NULL)
        {
            if(RF_Engine::instance->taskManager[i]->father == id)
            {
                RF_Engine::instance->taskManager[i]->signal = S_KILL_TREE;
            }
        }
    }
}
