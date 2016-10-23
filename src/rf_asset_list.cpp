#include "rf_asset_list.h"
#include "rf_engine.h"

#include <iostream>

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

    //Creamos un puntero con el que iremos seleccionando los ficheros
        FILE* fich;

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
                    int t = asset_type(ext);
                    if (t == 0) //Gfx2D
                    {
                        RF_Gfx2D* nA = new RF_Gfx2D(Aid, RF_Engine::instance->loadPNG_Surface(p.c_str()));
                        assets.push_back(nA);
                    }
                    else if(t == 1) //AudioClip
                    {
                        RF_AudioClip* nA = new RF_AudioClip(Aid, Mix_LoadMUS(p.c_str()));
                        assets.push_back(nA);
                    }
                    else if(t == 2) //TTF Font
                    {
                        RF_Font* nA = new RF_Font(Aid, TTF_OpenFont(p.c_str(),12), p);
                        assets.push_back(nA);
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
}
