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

        ~RF_AudioClip()
        {
            delete clip;
            clip = NULL;
        }

        Mix_Music* clip;
};

class RF_Gfx2D : public RF_Asset
{
    public:
        RF_Gfx2D(string name, SDL_Surface* gfx):RF_Asset(name)
        {
            texture = gfx;
        }

        ~RF_Gfx2D()
        {
            delete texture;
            texture = NULL;
        }

        SDL_Surface* texture;
};

class RF_Font : public RF_Asset
{
    public:
        RF_Font(string name, TTF_Font* ttf):RF_Asset(name)
        {
            font = ttf;
        }

        ~RF_Font()
        {
            delete font;
            font = NULL;
        }

        TTF_Font* font;
};
#endif // RF_ASSET_H
