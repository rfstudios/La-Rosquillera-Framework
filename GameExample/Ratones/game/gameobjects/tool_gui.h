#ifndef TOOL_GUI_H
#define TOOL_GUI_H

#include "rf_process.h"
#include "game.h"

class tool_gui : public RF_Process
{
    public:
        tool_gui(int t_id, Vector2<float> _pos) : RF_Process("tool_gui")
        {
            tool_id = t_id;
            pos = _pos;
        }
        ~tool_gui(){}

        virtual void Start()
        {
            string toolname;
            switch(tool_id)
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

            t_cont = Game::instance->tools_available[tool_id];
            graph = RF_Engine::instance->getGfx2D(toolname);
            transform.position = pos;
            Refresh();
        }

        virtual void Update()
        {
            transform.position = pos;
            if(Game::instance->tools_available[tool_id] != t_cont)
            {
                t_cont = Game::instance->tools_available[tool_id];
                Refresh();
            }
        }

        virtual void Refresh()
        {
            if(texto > -1)
            {
                RF_Engine::instance->deleteText(texto);
            }

            RF_Engine::instance->font = RF_Engine::instance->getFont("Times_New_Roman", 10);

            string t = to_string(Game::instance->tools_available[tool_id]);
            if(Game::instance->tools_available[tool_id] <= -1)
            {
                t = "No limit";
            }

            texto = RF_Engine::instance->write(("     " + t), {255,255,255}, transform.position);
        }

        int tool_id, t_cont;
        int texto = -1;

        Vector2<float> pos;
};
#endif // TOOL_GUI_H
