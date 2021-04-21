#include "..\..\include\audio\AudioEffect.h"

//default constructor setting all objects and variables to default value
AudioEffect::AudioEffect() : path(), mixEffect(NULL), effectType(AudioEffType::none) {}

//constructor setting path and effect type variable and also load content from file without information about validation
AudioEffect::AudioEffect(std::string path, AudioEffType effectType) : path(path), mixEffect(NULL), effectType(effectType) 
{ loadAudioFromFile(path, effectType); }

//simple destructor unbinding audio resource and delete a pointer
AudioEffect::~AudioEffect() { free(); delete mixEffect; }

//unbinds an audio resource and prepare to load again
void AudioEffect::free() { Mix_FreeChunk(mixEffect); mixEffect = NULL; effectType = AudioEffType::none; }

//load audio file from file and returning information about loading status
bool AudioEffect::loadAudioFromFile(std::string path, AudioEffType effectType)
{
	this->effectType = effectType;
	//loads audio from file (by SDL_mixer)
	mixEffect = Mix_LoadWAV(path.c_str());
	//if loading failed, show error message, reset effect type and return false
	if (mixEffect == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		effectType = AudioEffType::none;
		return false;
	}
	return true;
}

Mix_Chunk* AudioEffect::getEffect() { return mixEffect; }

AudioEffType AudioEffect::getEffectType() { return effectType; }

