#ifndef RF_SOUNDMANAGER_H
#define RF_SOUNDMANAGER_H

#include <string>
#include <SDL2/SDL_mixer.h>
using namespace std;

class RF_SoundManager
{
    public:
        RF_SoundManager(){}
        virtual ~RF_SoundManager(){}

        static void playSong(string file, int loop = -1);
        static void playSong(Mix_Music* clip, int loop = -1);

    private:
        static Mix_Music* music;
};

#endif // RF_SOUNDMANAGER_H
