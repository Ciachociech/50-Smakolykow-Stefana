#include "..\..\include\managers\AudioManager.h"

//returns Mix_Music (Music) object (raw SDL_mixer object) which is equal to argument value
Mix_Music* AudioManager::getMusic(AudioMusType musicType)
{
	for (int i = 0; i < audioMusics.size(); i++)
	{
		if (audioMusics[i]->getMusicType() == musicType) { return audioMusics[i]->getMusic(); }
	}
	return NULL;
}

//returns Mix_Chunk (Effect) object (raw SDL_mixer object) which is equal to argument value
Mix_Chunk* AudioManager::getEffect(AudioEffType effectType)
{
	for (int i = 0; i < audioEffects.size(); i++)
	{
		if (audioEffects[i]->getEffectType() == effectType) { return audioEffects[i]->getEffect(); }
	}
	return NULL;
}

AudioManager::AudioManager() : effectVolume(8), musicVolume(8) {}

AudioManager::~AudioManager() { exterminate(); }

//deletes all loaded AudioMusic and AudioEffect objects and at the end clear both vectors
void AudioManager::exterminate()
{
	for (int i = 0; i < audioMusics.size(); i++) { audioMusics[i]->free(); }
	for (int i = 0; i < audioEffects.size(); i++) { audioEffects[i]->free(); }

	audioMusics.clear();
	audioEffects.clear();
}

//loads audio content from assets files to proper vector of AudioMusic/AudioEffect objects
bool AudioManager::initAudios()
{
	bool success = true;

	//Load music (create at the beginning temporary AudioMusic to load audio from file to variable and save to vector)
	AudioMusic tempMusic = AudioMusic();
	success = success && tempMusic.loadAudioFromFile("Assets/audio/32sec-of-silence.mid", AudioMusType::music);
	audioMusics.push_back(std::make_unique<AudioMusic>(tempMusic));
	success = success && tempMusic.loadAudioFromFile("Assets/audio/stefan-menu-theme.mp3", AudioMusType::menuPreTheme);
	audioMusics.push_back(std::make_unique<AudioMusic>(tempMusic));
	success = success && tempMusic.loadAudioFromFile("Assets/audio/stubborntunism-theme.mp3", AudioMusType::stubborntunismTheme);
	audioMusics.push_back(std::make_unique<AudioMusic>(tempMusic));
	success = success && tempMusic.loadAudioFromFile("Assets/audio/gameover.wav", AudioMusType::gameover);
	audioMusics.push_back(std::make_unique<AudioMusic>(tempMusic));
	success = success && tempMusic.loadAudioFromFile("Assets/audio/levelup.wav", AudioMusType::levelup);
	audioMusics.push_back(std::make_unique<AudioMusic>(tempMusic));
	//to save last element, load without saving empty MIDI file (I know there is a strange fix to this bug)
	success = success && tempMusic.loadAudioFromFile("Assets/audio/32sec-of-silence.mid", AudioMusType::none);

	//Load sound effects (create at the beginning temporary AudioEffect to load audio from file to variable and save to vector)
	AudioEffect tempEffect = AudioEffect();
	success = success && tempEffect.loadAudioFromFile("Assets/audio/jump.wav", AudioEffType::jump);
	audioEffects.push_back(std::make_unique<AudioEffect>(tempEffect));
	success = success && tempEffect.loadAudioFromFile("Assets/audio/bonk.wav", AudioEffType::bonk);
	audioEffects.push_back(std::make_unique<AudioEffect>(tempEffect));
	success = success && tempEffect.loadAudioFromFile("Assets/audio/dig-none.wav", AudioEffType::digNone);
	audioEffects.push_back(std::make_unique<AudioEffect>(tempEffect));
	success = success && tempEffect.loadAudioFromFile("Assets/audio/dignine-none.wav", AudioEffType::dignineNone);
	audioEffects.push_back(std::make_unique<AudioEffect>(tempEffect));
	success = success && tempEffect.loadAudioFromFile("Assets/audio/nosescan.wav", AudioEffType::nosescan);
	audioEffects.push_back(std::make_unique<AudioEffect>(tempEffect));
	success = success && tempEffect.loadAudioFromFile("Assets/audio/point-gaining.wav", AudioEffType::pointGaining);
	audioEffects.push_back(std::make_unique<AudioEffect>(tempEffect));
	//to save last element, load without saving some WAV file (I know there is a strange fix to this bug)
	success = success && tempEffect.loadAudioFromFile("Assets/audio/bonk.wav", AudioEffType::none);					//to save last element

	return success;

}

//play selected AudioEffect (by chosen effect type), it is highly recommended to invoke this method with channel = -1 and repeats = 0 (or without giving this argument). Before playing sound it is included the volume of sound.
void AudioManager::playEffect(AudioEffType effectType, int channel, int repeats) 
{ 
	Mix_VolumeChunk(getEffect(effectType), (MIX_MAX_VOLUME / 16) * effectVolume);
	Mix_PlayChannel(channel, getEffect(effectType), repeats); 
}

//play selected AudioMusic (by chosen music type), it is recommended to invoke this method with repeats = -1 (or without giving this argument) to play music in loop. Before playing sound it is included the volume of sound.
void AudioManager::playMusic(AudioMusType musicType, int repeats) 
{ 
	Mix_VolumeMusic((MIX_MAX_VOLUME / 16) * musicVolume);
	Mix_PlayMusic(getMusic(musicType), repeats); 
}

//pause current played music
void AudioManager::pauseMusic() { Mix_PauseMusic(); }

//unpause current paused (previously played) music
void AudioManager::resumeMusic() { Mix_ResumeMusic(); }

//stop current played or paused music
void AudioManager::stopMusic() { Mix_HaltMusic(); }

void AudioManager::stopChannel(int channel) { Mix_HaltChannel(channel);  }

void AudioManager::setMusicVolume(int volume) { if (volume >= 0 || volume <= 16) { this->musicVolume = volume; } }

void AudioManager::setEffectVolume(int volume) { if (volume >= 0 || volume <= 16) { this->effectVolume = volume; } }
