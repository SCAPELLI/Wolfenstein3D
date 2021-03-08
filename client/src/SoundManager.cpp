#include "client/include/SoundManager.h"
#include <string>

#define ROUTE "../../client/sounds/"
#define EFFECT_EXTENTION ".wav"
#define MAX_EFFECTS 8

SoundManager::SoundManager():
    music(Mix_LoadMUS((ROUTE + std::string("music.mp3")).c_str())),
    musicIsPlaying(false)
    {
    for (int i = 0; i < MAX_EFFECTS; i++) {
        soundEffects.emplace_back(Mix_LoadWAV((ROUTE + std::to_string(i) + EFFECT_EXTENTION).c_str()));
    }
}

void SoundManager::push(int soundId, int volume) {
    Mix_Chunk* sound = soundEffects[soundId];
    Mix_VolumeChunk(sound, volume);
    toPlay.push_back(sound);
}
void SoundManager::playSounds() {
    for (int i = 0; i < toPlay.size() && i < 8; i++){
        Mix_PlayChannel(-1, toPlay[i], 0);
    }
    if (!musicIsPlaying){
        Mix_PlayMusic(music, -1);
        musicIsPlaying = true;
    }
    toPlay.clear();
}

SoundManager::~SoundManager(){
    for (int i = 0; i < MAX_EFFECTS; i++) {
        Mix_FreeChunk(soundEffects[i]);
    }
    Mix_FreeMusic(music);
    Mix_Quit();
}