#ifndef WOLF_SOUNDMANAGER_H
#define WOLF_SOUNDMANAGER_H

#include <SDL_mixer.h>
#include <vector>
/* Manejador de los sonidos del cliente*/
class SoundManager {
    Mix_Music* music;
    bool musicIsPlaying;
    std::vector<Mix_Chunk*> soundEffects;
    std::vector<Mix_Chunk*> toPlay;
    public:
        SoundManager();
        void push(int soundId, int volume);
        void playSounds();
       ~SoundManager();
};


#endif //WOLF_SOUNDMANAGER_H
