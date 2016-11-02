#ifndef RF_SOUNDMANAGER_H
#define RF_SOUNDMANAGER_H

#include "rf_process.h"
#include <string>
#include <SDL2/SDL_mixer.h>
using namespace std;

class RF_SoundTransition : public RF_Process
{
    public:
        RF_SoundTransition(){}
        ~RF_SoundTransition(){}

        virtual void Start()
        {
            Mix_FadeOutMusic(500);
        }

        virtual void Update();

        bool changed = false;
};

class RF_SoundManager
{
    friend void RF_SoundTransition::Update();

    public:
        RF_SoundManager(){}
        virtual ~RF_SoundManager(){}

        static void playFX(string file, int channel = -1);
        static void playFX(Mix_Chunk* clip, int channel = -1);

        static void playSong(string file, int loop = -1);
        static void playSong(Mix_Music* clip, int loop = -1);

        static void changeMusic(string file);
        static void changeMusic(Mix_Music* clip);

    private:
        static Mix_Music* music;
        static Mix_Music* cMusic;
        int vol = 100;
};
#endif // RF_SOUNDMANAGER_H
