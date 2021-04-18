#pragma once

#include "external_dependencies.h"

//enum with type of audio effect
enum class AudioEffType { none = 0, jump = 1, bonk, digNone, dignineNone, nosescan, pointGaining };

class AudioEffect
{
private:
	std::string path;											//path of audio source
	Mix_Chunk* mixEffect;										//mix music object
	AudioEffType effectType;									//type of audio music
public:
	AudioEffect();
	AudioEffect(std::string path, AudioEffType effectType);
	virtual ~AudioEffect();
	void free();

	bool loadAudioFromFile(std::string path, AudioEffType effectType);
	Mix_Chunk* getEffect();
	AudioEffType getEffectType();
};

