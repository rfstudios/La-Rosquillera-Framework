#ifndef GAME_H
#define GAME_H

#include "rf_process.h"
#include "rf_engine.h"
#include <vector>
using namespace std;

class Node : public RF_Process
{
    public:
        Node():RF_Process("node"){}
        ~Node(){}
};

struct Score{
    int value;
    int victory;
    int color;
    int text;
    Vector2<int> pos;

    Score(int _value, int _victory, int _color, Vector2<int> _pos)
    {
        color = _color;
        value = _value;
        victory = _victory;
        pos = _pos;
        text = -1;

        Refresh();
    }

    void Refresh()
    {
        if(text > -1)
        {
            RF_Engine::instance->deleteText(text);
        }

        string tmpCol;
        switch(color)
        {
            case SPAWN_RED:
                tmpCol="Red";
                break;
            case SPAWN_GREEN:
                tmpCol="Green";
                break;
            case SPAWN_YELLOW:
                tmpCol="Yellow";
                break;
            case SPAWN_BLUE:
                tmpCol="Blue";
                break;
        }
        text = RF_Engine::instance->write((tmpCol + ": " + to_string(value) + "/" + to_string(victory)), {255,255,255}, pos);
    }
};

class Game : public RF_Process
{
    public:
        static Game* instance;

        Game():RF_Process("Game")
        {
            instance = this;

            RF_Engine::instance->loadAsset("resources/spawners");
            RF_Engine::instance->loadAsset("resources/mouses");
            RF_Engine::instance->loadAsset("resources/madrigueras");
            RF_Engine::instance->loadAsset("resources/world");
        }
        virtual ~Game(){}

        virtual void Start();
        virtual void Update();

        void parseLevel();
        void PlaceNode(int node, Vector2<int> pos);
        void SetPoint(int col);
        int Plataformas[64][48];
        void ChangeTool();
        bool checkVictory();
        void callLevel(int l);

        vector<Score> scores;
        int population[4];
        int vict[4];
        int lvl = 1;
        Vector2<float> mouseSpeed;

        int selectedTool = 1;
        bool pressed = false;
        int gameStatus = 0;
};

#endif // GAME_H
