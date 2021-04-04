#pragma once

#include "external_dependencies.h"

//enum with type of audio music
enum class AudioMusType { none = 0, music = 1, menuPreTheme };

class AudioMusic
{
private:
	std::string path;											//path of audio source
	Mix_Music* mixMusic;										//mix music object
	AudioMusType musicType;										//type of audio music
public:
	AudioMusic();
	AudioMusic(std::string path, AudioMusType musicType);
	virtual ~AudioMusic();
	void free();

	bool loadAudioFromFile(std::string path, AudioMusType musicType);
	Mix_Music* getMusic();
	AudioMusType getMusicType();
};

