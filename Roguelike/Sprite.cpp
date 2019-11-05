#include "Sprite.h"

Sprite::Sprite(int x, int y, SDL_Color color)
	: mGraphics(Graphics::Instance()), mColor(color)
{
	mTexture = AssetManager::Instance().GetTexture("tilesheet.png");

	mClipRect.x = x * TILE_SIZE + x;
	mClipRect.y = y * TILE_SIZE + y;

	mClipRect.w = TILE_SIZE;
	mClipRect.h = TILE_SIZE;
}


Sprite::~Sprite()
{
}


void Sprite::Draw(int x, int y, bool ignoreCamera)
{
	SDL_Rect renderRect;

	renderRect.x = x * TILE_SIZE;
	renderRect.y = y * TILE_SIZE;
	renderRect.w = mClipRect.w;
	renderRect.h = mClipRect.h;

	SDL_SetTextureColorMod(mTexture.get(), mColor.r, mColor.g, mColor.b);

	mGraphics.DrawTexture(mTexture, &mClipRect, &renderRect, ignoreCamera);

	SDL_SetTextureColorMod(mTexture.get(), 255, 255, 255);
}