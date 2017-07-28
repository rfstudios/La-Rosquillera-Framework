#include "rf_asset_list.h"
#include "rf_engine.h"
#include "rf_primitive.h"

#include "NLTmxMap.h"
#include <fstream>

RF_Asset_List::~RF_Asset_List()
{
    int pos = -1; unsigned int i;
    for(i = 0; i < assets.size(); i++)
    {
        delete assets[i];
    }
    assets.clear();
}

RF_Asset_List::RF_Asset_List(string path)
{
    ///Por el momento, path es un directorio

    //Obtenemos el id del paquete de recursos
        const size_t it = path.find_last_of('/');
        id = path; id.erase(0,it+1);

    //Extraemos el nombre del directorio para insertarlo en el nombre;
        DIR *dir;

    //En *ent habrá información sobre el archivo que se está "sacando" a cada momento;
        struct dirent *ent;

    //Empezaremos a leer en el directorio actual;
        dir = opendir (path.c_str());

    //Miramos que no haya error
        if (dir == NULL)
        {
            RF_Engine::instance->Debug(("LoadAsset [Error]: No se puede abrir directorio " + path));
            return;
        }

    //Creamos un puntero con el seleccionaremos el fichero de configuración (si existe);
        ifstream fich(path + "/package.cfg");

        if(fich.is_open())
        {
            RF_Engine::instance->Debug((path + "/package.cfg"));

            string buffer;
            while(!fich.eof())
            {
                fich >> buffer;
                cfg.push_back(buffer);
            }
        }

    //Leyendo uno a uno todos los archivos que hay
        while ((ent = readdir (dir)) != NULL)
        {
            //Los ficheros "." y ".." son punteros al directorio actual y al directamente superior
                if((strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0))
                {
                    string ext = ent->d_name;
                    const size_t pos = ext.find_last_of('.');
                    string Aid = ext; Aid.erase(pos);
                    ext.erase(0,pos+1);

                    string p = path + "/" + ent->d_name;
                    string opc = getConfig(Aid);

                    int t = asset_type(ext);
                    if (t == 0) //Gfx2D
                    {
                        if(opc != "MultiSprite")
                        {
                            RF_Gfx2D* nA = new RF_Gfx2D(Aid, RF_Engine::instance->loadPNG_Surface(p.c_str()));
                            assets.push_back(nA);
                        }
                        else
                        {
                            Vector2<int> size = getMultiSpriteConfig(Aid,path);
                            SDL_Surface* srf = RF_Engine::instance->loadPNG_Surface(p.c_str());
                            Vector2<int> scale(srf->w / size.x, srf->h / size.y);
                            SDL_Surface* dest = NULL;

                            for(int i = 0; i < size.x; i++)
                            {
                                for(int j = 0; j < size.y; j++)
                                {
                                    dest = SDL_CreateRGBSurface(0, scale.x, scale.y, srf->format->BitsPerPixel, 0,0,0,0);

                                    for(int ii = 0; ii < scale.x; ii++)
                                    {
                                        for(int jj = 0; jj < scale.y; jj++)
                                        {
                                            RF_Primitive::putPixel(dest, ii, jj, RF_Primitive::getPixel(srf, ii + scale.x*i, jj + scale.y*j));
                                        }
                                    }

                                    RF_Gfx2D* push = new RF_Gfx2D((Aid + "_" + to_string(i) + "_" + to_string(j)),dest);
                                    assets.push_back(push);
                                }
                            }

                            SDL_FreeSurface(srf);

                            RF_MultiSprite_Info* nI = new RF_MultiSprite_Info((Aid + "_info"),Vector2<int>(size));
                            assets.push_back(nI);
                        }
                    }
                    else if(t == 1) //AudioClip
                    {
                        if(opc == "-1") {opc = getConfig("AllAudio");}

                        if(opc == "fx")
                        {
                            RF_FXClip* nA = new RF_FXClip(Aid, Mix_LoadWAV(p.c_str()));
                            assets.push_back(nA);
                        }
                        else
                        {
                            RF_AudioClip* nA = new RF_AudioClip(Aid, Mix_LoadMUS(p.c_str()));
                            assets.push_back(nA);
                        }
                    }
                    else if(t == 2) //TTF Font
                    {
                        int pt = stoi(opc);
                        if(pt == -1){pt = 12;}
                        else if(pt < 1){pt = 1;}

                        RF_Font* nA = new RF_Font(Aid, TTF_OpenFont(p.c_str(),pt), p);
                        assets.push_back(nA);
                    }
                    else if(t == 3) //Tiled Map
                    {
                        char * xml = (char*) loadFile(p.c_str(), true);
                        NLTmxMap* map = NLLoadTmxMap(xml);
                        RF_Tiled_Map* nTM = new RF_Tiled_Map(Aid, map);

                        assets.push_back(nTM);
                    }
                }
        }

        RF_Engine::instance->Debug(("LoadAsset [Info]: " + id + " done"));
}

int RF_Asset_List::asset_type(string ext)
{
    if(ext == "png" or ext == "jpg")
    {
        return 0; //Gfx2D
    }
    else if(ext == "wav" or ext == "mp3" or ext == "ogg")
    {
        return 1; //Snd
    }
    else if(ext == "ttf")
    {
        return 2; //Ttf
    }
    else if(ext == "tmx")
    {
        return 3; //Tiled
    }

    return -1;
}

string RF_Asset_List::getConfig(string file)
{
    string ret = "-1";
    if(cfg.size() < 1){return ret;}

    for(int i = 0; i <= cfg.size()-1 && ret == "-1"; i++)
    {
        string f = cfg[i];
        if(f == file && i < cfg.size()-3)
        {
            ret = cfg[i+2];
        }
    }

    return ret;
}

Vector2<int> RF_Asset_List::getMultiSpriteConfig(string file, string path)
{
    ifstream fich(path + "/" + file + ".cfg");
    Vector2<int> ret(0,0);

    if(fich.is_open())
    {
        RF_Engine::instance->Debug((path + "/" + file + ".cfg"));

        vector<string> mcfg;

        string buffer;
        while(!fich.eof())
        {
            fich >> buffer;
            mcfg.push_back(buffer);
        }

        for(int i = 0; i <= mcfg.size()-1 && (ret.x == 0 || ret.y == 0); i++)
        {
            string f = mcfg[i];
            if(f == "width")
            {
                ret.x = atoi(mcfg[i+2].c_str());
            }
            if(f == "height")
            {
                ret.y = atoi(mcfg[i+2].c_str());
            }
        }
    }

    return ret;
}
