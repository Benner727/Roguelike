#include "Audio.h"

Audio& Audio::Instance()
{
	static Audio instance;
	return instance;
}

int Audio::MusicVolume() const
{
	return mMusicVolume;
}

void Audio::MusicVolume(int volume)
{
	if (volume < 0 || volume > FULL_VOLUME)
		return;

	mMusicVolume = volume;
	Mix_VolumeMusic(MIX_MAX_VOLUME * (float)(mMusicVolume / FULL_VOLUME));
}

int Audio::SFXVolume() const
{
	return mSFXVolume;
}

void Audio::SFXVolume(int volume, int channel)
{
	if (volume < 0 || volume > FULL_VOLUME)
		return;

	mSFXVolume = volume;
	Mix_Volume(channel, MIX_MAX_VOLUME * (float)(mSFXVolume / FULL_VOLUME));
}

Audio::Audio()
	: mAssetManager(AssetManager::Instance())
{
	mMusicVolume = FULL_VOLUME;
	mSFXVolume = FULL_VOLUME;

	int flags = MIX_INIT_OGG | MIX_INIT_MP3;
	if (!Mix_Init(flags) & flags)
		std::cout << "Mixer Initialization Error: " << Mix_GetError() << std::endl;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		std::cout << "Mixer Initialization Error: " << Mix_GetError() << std::endl;
}

Audio::~Audio()
{
	Mix_Quit();
}

void Audio::PlayMusic(const std::string& filename, int loops)
{
	Mix_PlayMusic(mAssetManager.GetMusic("Audio/" + filename).get(), loops);
}

void Audio::PauseMusic()
{
	if (Mix_PlayingMusic() != 0)
		Mix_PauseMusic();
}

void Audio::ResumeMusic()
{
	if (Mix_PausedMusic() != 0)
		Mix_ResumeMusic();
}

void Audio::PlaySFX(const std::string& filename, int loops, int channel, bool playover)
{
	if (playover || !Mix_Playing(channel))
		Mix_PlayChannel(channel, mAssetManager.GetSFX("Audio/" + filename).get(), loops);
}

void Audio::StopSFX(int channel)
{
	Mix_HaltChannel(channel);
}