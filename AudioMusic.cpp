#include "AudioMusic.h"

//default constructor setting all objects and variables to default value
AudioMusic::AudioMusic() : path(), mixMusic(NULL), musicType(AudioMusType::none) {}

//constructor setting path and music type variable and also load content from file without information about validation
AudioMusic::AudioMusic(std::string path, AudioMusType musicType) : path(path), mixMusic(NULL), musicType(musicType) { loadAudioFromFile(path, musicType); }

//simple destructor unbinding audio resource and delete a pointer
AudioMusic::~AudioMusic() { free(); delete mixMusic; }

//unbinds an audio resource and prepare to load again
void AudioMusic::free() { Mix_FreeMusic(mixMusic); mixMusic = NULL; musicType = AudioMusType::none; }

//load audio file from file and returning information about loading status
bool AudioMusic::loadAudioFromFile(std::string path, AudioMusType musicType)
{
	this->musicType = musicType;
	//loads audio from file (by SDL_mixer)
	mixMusic = Mix_LoadMUS(path.c_str());
	//if loading failed, show error message, reset effect type and return false
	if (mixMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		musicType = AudioMusType::none;
		return false;
	}
	return true;
}

Mix_Music* AudioMusic::getMusic() { return mixMusic; }

AudioMusType AudioMusic::getMusicType() { return musicType; }

