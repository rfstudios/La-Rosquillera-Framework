#include "rf_soundmanager.h"
#include "rf_engine.h"

Mix_Music* RF_SoundManager::music;

void RF_SoundManager::playSong(string file, int loop)
{
        playSong(RF_Engine::instance->getAudioClip(file),loop);
}

void RF_SoundManager::playSong(Mix_Music* clip, int loop)
{
        if(NULL != music)
        {
            Mix_FreeMusic(music);
        }

        music = clip;
        Mix_PlayMusic(music, loop);
}
