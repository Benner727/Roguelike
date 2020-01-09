#include "Sprite.h"

Sprite::Sprite(int x, int y, SDL_Color color)
	: mGraphics(Graphics::Instance()), mColor(color)
{
	mTexture = AssetManager::Instance().GetTexture("tilesheet.png");

	SDL_SetTextureBlendMode(mTexture.get(), SDL_BLENDMODE_BLEND);

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

	renderRect.x = x * TILE_SIZE * 1.5f;
	renderRect.y = y * TILE_SIZE * 1.5f;
	renderRect.w = mClipRect.w * 1.5f;
	renderRect.h = mClipRect.h * 1.5f;

	SDL_SetTextureColorMod(mTexture.get(), mColor.r, mColor.g, mColor.b);

	mGraphics.DrawTexture(mTexture, &mClipRect, &renderRect, 0.0f, SDL_FLIP_NONE, ignoreCamera);

	SDL_SetTextureColorMod(mTexture.get(), 255, 255, 255);
}