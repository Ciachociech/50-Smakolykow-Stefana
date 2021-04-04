#pragma once

#include <vector>
#include <memory>

#include "AudioMusic.h"
#include "AudioEffect.h"

typedef std::vector<std::unique_ptr<AudioMusic>> VecMusics;
typedef std::vector<std::unique_ptr<AudioEffect>> VecEffects;

class AudioManager
{
private:
	VecMusics audioMusics;									//vector of AudioMusic objects
	VecEffects audioEffects;								//vector of AudioEffect objects

	Mix_Music* getMusic(AudioMusType musicType);
	Mix_Chunk* getEffect(AudioEffType effectType);
public:
	AudioManager();
	virtual ~AudioManager();
	void exterminate();

	bool initAudios();
	void playEffect(AudioEffType effectType, int channel, int repeats = 0);
	void playMusic(AudioMusType musicType, int repeats = -1);
	void pauseMusic();
	void resumeMusic();
	void stopMusic();
};

