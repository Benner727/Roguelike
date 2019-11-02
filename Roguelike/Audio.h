#ifndef AUDIO_H
#define AUDIO_H

#include "AssetManager.h"

class Audio
{
private:
	static const int FULL_VOLUME = 100;

	AssetManager& mAssetManager;

	int mMusicVolume;
	int mSFXVolume;

	Audio();
	~Audio();

public:
	static Audio& Instance();

	int MusicVolume() const;
	void MusicVolume(int volume);
	int SFXVolume() const;
	void SFXVolume(int volume, int channel = 0);

	void PlayMusic(const std::string& filename, int loops = -1);
	void PauseMusic();
	void ResumeMusic();

	void PlaySFX(const std::string&, int loops = 0, int channel = 0, bool playover = true);
	void StopSFX(int channel = -1);
};

#endif