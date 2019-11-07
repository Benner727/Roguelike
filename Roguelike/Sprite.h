#ifndef SPRITE_H
#define SPRITE_H

#include "AssetManager.h"

class Sprite
{
public:
	static const int TILE_SIZE = 16;

	Sprite(int x, int y, SDL_Color color);
	~Sprite();

private:
	Graphics& mGraphics;
	std::shared_ptr<SDL_Texture> mTexture;

	SDL_Rect mClipRect;
	SDL_Color mColor;

public:
	void Color(SDL_Color color) { mColor = color; }

	void Draw(int x, int y, bool ignoreCamera = false);
};

#endif