#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SDL_mixer.h>
#include <map>

#include "Graphics.h"

class AssetManager
{
private:
	std::unique_ptr<std::string> mBasePath;

	std::map<std::string, std::shared_ptr<SDL_Texture>> mTextures;
	std::map<std::string, std::shared_ptr<SDL_Texture>> mText;
	std::map<std::string, std::shared_ptr<TTF_Font>> mFonts;
	std::map<std::string, std::shared_ptr<Mix_Music>> mMusic;
	std::map<std::string, std::shared_ptr<Mix_Chunk>> mSFX;

	AssetManager();
	~AssetManager();

	std::weak_ptr<TTF_Font> GetFont(const std::string& filename, int size);

public:
	static AssetManager& Instance();

	const std::string& GetBasePath() { return *mBasePath; }

	std::shared_ptr<SDL_Texture> GetTexture(const std::string& filename);
	std::shared_ptr<SDL_Texture> GetText(const std::string& text, const std::string& filename, int size, SDL_Color color);

	std::shared_ptr<Mix_Music> GetMusic(const std::string& filename);
	std::shared_ptr<Mix_Chunk> GetSFX(const std::string& filename);
};

#endif