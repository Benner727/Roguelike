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


Sprite::Sprite(int x, int y, SDL_Color color, int fixedX, int fixedY)
	: mGraphics(Graphics::Instance()), mColor(color)
{
	mTexture = AssetManager::Instance().GetTexture("tilesheet.png");

	SDL_SetTextureBlendMode(mTexture.get(), SDL_BLENDMODE_BLEND);

	mClipRect.x = x * TILE_SIZE + x;
	mClipRect.y = y * TILE_SIZE + y;

	mClipRect.w = TILE_SIZE;
	mClipRect.h = TILE_SIZE;

	mPositionX = fixedX;
	mPositionY = fixedY;
}


Sprite::~Sprite()
{
}


void Sprite::DrawFixed(bool ignoreCamera, float scale, int offset_x, int offset_y)
{
	Draw(mPositionX, mPositionY, ignoreCamera, scale, offset_x, offset_y);
}

void Sprite::Draw(int x, int y, bool ignoreCamera, float scale, int offset_x, int offset_y)
{
	SDL_Rect renderRect;

	renderRect.x = x * TILE_SIZE * scale + (offset_x);
	renderRect.y = y * TILE_SIZE * scale + (offset_y);
	renderRect.w = mClipRect.w * scale;
	renderRect.h = mClipRect.h * scale;

	SDL_SetTextureColorMod(mTexture.get(), mColor.r, mColor.g, mColor.b);

	mGraphics.DrawTexture(mTexture, &mClipRect, &renderRect, 0.0f, SDL_FLIP_NONE, ignoreCamera);

	SDL_SetTextureColorMod(mTexture.get(), 255, 255, 255);
}