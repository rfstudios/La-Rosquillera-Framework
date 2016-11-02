#ifndef RF_ASSET_H
#define RF_ASSET_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>
using namespace std;

class RF_Asset
{
    public:
        RF_Asset(string name){ id = name;}
        virtual ~RF_Asset(){}

        string id;
};

class RF_AudioClip : public RF_Asset
{
    public:
        RF_AudioClip(string name, Mix_Music* a):RF_Asset(name)
        {
            clip = a;
        }

        virtual ~RF_AudioClip()
        {
            Mix_FreeMusic(clip);
            delete clip;
            clip = NULL;
        }

        Mix_Music* clip;
};

class RF_FXClip : public RF_Asset
{
    public:
        RF_FXClip(string name, Mix_Chunk* a):RF_Asset(name)
        {
            clip = a;
        }

        virtual ~RF_FXClip()
        {
            Mix_FreeChunk(clip);
            delete clip;
            clip = NULL;
        }

        Mix_Chunk* clip;
};

class RF_Gfx2D : public RF_Asset
{
    public:
        RF_Gfx2D(string name, SDL_Surface* gfx):RF_Asset(name)
        {
            surface = gfx;
            texture = NULL;
        }
        RF_Gfx2D(string name, SDL_Texture* gfx):RF_Asset(name)
        {
            texture = gfx;
        }

        virtual ~RF_Gfx2D()
        {
            if(texture != NULL)
            {
                SDL_DestroyTexture(texture);
            }
            texture = NULL;

            if(surface != NULL)
            {
                SDL_FreeSurface(surface);
            }
            surface = NULL;
        }

        SDL_Surface* surface;
        SDL_Texture* texture;
};

class RF_Font : public RF_Asset
{
    public:
        RF_Font(string name, TTF_Font* ttf, string _path):RF_Asset(name)
        {
            path = _path;
            font = ttf;
        }

        virtual ~RF_Font()
        {
            delete font;
            font = NULL;
        }

        TTF_Font* font;
        string path;
};
#endif // RF_ASSET_H
