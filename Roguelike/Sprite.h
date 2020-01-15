#ifndef SPRITE_H
#define SPRITE_H

#include "AssetManager.h"

class Sprite
{
public:
	static const int TILE_SIZE = 16;

	Sprite(int x, int y, SDL_Color color);
	Sprite(int x, int y, SDL_Color color, int fixedX, int fixedY);
	~Sprite();

private:
	Graphics& mGraphics;
	std::shared_ptr<SDL_Texture> mTexture;

	SDL_Rect mClipRect;
	SDL_Color mColor;

	int mPositionX;
	int mPositionY;

public:
	void Color(SDL_Color color) { mColor = color; }

	void Alpha(int alpha) { SDL_SetTextureAlphaMod(mTexture.get(), alpha); }
	void DrawFixed(bool ignoreCamera = false, float scale = 1.5f, int offset_x = 0, int offset_y = 0);
	void Draw(int x, int y, bool ignoreCamera = false, float scale = 1.5f, int offset_x = 0, int offset_y = 0);
};

#endif