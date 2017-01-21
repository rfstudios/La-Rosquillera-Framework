#include "game.h"
#include "mainprocess.h"
#include "raton.h"

#include "gameobjects/spawner.h"
#include "gameobjects/madriguera.h"
#include "gameobjects/dureza.h"
#include "gameobjects/splitter.h"
#include "gameobjects/elevator.h"
#include "gameobjects/colorchanger.h"

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

            if(Raton::instance->OnClick)
            {
                RF_Process* aux = RF_Engine::instance->collision("node",Raton::instance);
                if(aux)
                {
                    RF_Engine::instance->sendSignal(aux->id,S_KILL_TREE);
                }

                PlaceNode(selectedTool,Vector2<int>((int)Raton::instance->transform.position.x/10,(int)Raton::instance->transform.position.y/10));

                pressed = true;
            }
        }
        else
        {
            if(!RF_Engine::instance->key[_space] && !Raton::instance->OnClick)
            {
                pressed = false;
            }
        }
    }
    else if(gameStatus == 1)
    {
        RF_Engine::instance->sendSignal(id,S_KILL_CHILD);
        RF_Engine::instance->sendSignal("NPC_Raton",S_KILL_TREE);
        RF_Engine::instance->sendSignal("Madriguera",S_KILL_TREE);
        RF_Engine::instance->sendSignal("Spawner",S_KILL_TREE);
        RF_Engine::instance->sendSignal("Node",S_KILL_TREE);
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
    selectedTool++;
    if(selectedTool > 4){selectedTool = 0;}

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
    }

    Raton::instance->graph = RF_Engine::instance->getGfx2D(toolname);
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
            Levels::Level20();
            break;

        default:
            RF_Engine::instance->sendSignal("NPC_Raton",S_KILL_TREE);
            RF_Engine::instance->sendSignal("Madriguera",S_KILL_TREE);
            RF_Engine::instance->sendSignal("Spawner",S_KILL_TREE);
            RF_Engine::instance->sendSignal("Node",S_KILL_TREE);
            dynamic_cast<mainProcess*>(RF_Engine::instance->taskManager[father])->state() = 3;
            break;
    }

    parseLevel();

    gameStatus = 0;
}
