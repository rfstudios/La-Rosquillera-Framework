#include "rf_soundmanager.h"
#include "rf_engine.h"

Mix_Music* RF_SoundManager::music;
Mix_Music* RF_SoundManager::cMusic;

void RF_SoundManager::playFX(string file, int channel)
{
        playFX(RF_Engine::instance->getFXClip(file),channel);
}

void RF_SoundManager::playFX(Mix_Chunk* clip, int channel)
{
    Mix_PlayChannel(channel, clip, 0);
}

void RF_SoundManager::playSong(string file, int loop)
{
        playSong(RF_Engine::instance->getAudioClip(file),loop);
}

void RF_SoundManager::playSong(Mix_Music* clip, int loop)
{
        music = clip;
        Mix_PlayMusic(music, loop);
}

void RF_SoundManager::changeMusic(string file)
{
        changeMusic(RF_Engine::instance->getAudioClip(file));
}

void RF_SoundManager::changeMusic(Mix_Music* clip)
{
        if(NULL == music)
        {
            playSong(clip,-1);
        }
        else
        {
            if(cMusic == NULL)
            {
                cMusic = clip;

                if(cMusic == music)
                {
                    RF_Engine::instance->Debug("SoundManager [Error]: Ya está sonando el audio indicado por lo que se descarta la transición");
                    cMusic = NULL;
                }
                else
                {
                    RF_Engine::instance->newTask(new RF_SoundTransition(),-1);
                }
            }
            else
            {
                RF_Engine::instance->Debug("SoundManager [Error]: Ya hay una transición en marcha");
            }
        }
}

void RF_SoundTransition::Update()
{
    if(!changed)
    {
        if(Mix_FadingMusic() == MIX_NO_FADING)
        {
            RF_SoundManager::music = RF_SoundManager::cMusic;
            RF_SoundManager::cMusic = NULL;
            Mix_FadeInMusic(RF_SoundManager::music, -1, 500);

            changed = true;
        }
    }
    else
    {
        if(Mix_FadingMusic() == MIX_NO_FADING)
        {
            RF_Engine::instance->sendSignal(id,S_KILL);
        }
    }
}
