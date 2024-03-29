#pragma once

#include <vector>
#include <memory>

#include "..\audio\AudioEffect.h"
#include "..\audio\AudioMusic.h"

typedef std::vector<std::unique_ptr<AudioMusic>> VecMusics;
typedef std::vector<std::unique_ptr<AudioEffect>> VecEffects;

class AudioManager
{
private:
	VecMusics audioMusics;									//vector of AudioMusic objects
	VecEffects audioEffects;								//vector of AudioEffect objects

	Mix_Music* getMusic(AudioMusType musicType);
	Mix_Chunk* getEffect(AudioEffType effectType);

	int musicVolume;
	int effectVolume;
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
	void stopChannel(int channel);

	void setMusicVolume(int volume);
	void setEffectVolume(int volume);
};

