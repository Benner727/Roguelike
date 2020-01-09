#include "Texture.h"



Texture::Texture(const std::string & filename)
	: mGraphics(Graphics::Instance())
{
	mPos = { 0, 0 };
	mRotation = 0.0f;
	mScaleX = 1.0f;
	mScaleY = 1.0f;

	mTexture = AssetManager::Instance().GetTexture(filename);
	SDL_QueryTexture(mTexture.get(), nullptr, nullptr, &mWidth, &mHeight);
	SDL_SetTextureBlendMode(mTexture.get(), SDL_BLENDMODE_BLEND);

	mClipped = false;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;

	mFlip = SDL_FLIP_NONE;
	mColor = { 255, 255, 255, 255 };
}

Texture::Texture(const std::string & filename, int x, int y, int w, int h)
	: mGraphics(Graphics::Instance())
{
	mPos = { 0, 0 };
	mRotation = 0.0f;
	mScaleX = 1.0f;
	mScaleY = 1.0f;

	mTexture = AssetManager::Instance().GetTexture(filename);
	SDL_SetTextureBlendMode(mTexture.get(), SDL_BLENDMODE_BLEND);

	mClipped = true;

	mWidth = w;
	mHeight = h;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;

	mClipRect.x = x;
	mClipRect.y = y;
	mClipRect.w = mWidth;
	mClipRect.h = mHeight;

	mFlip = SDL_FLIP_NONE;
	mColor = { 255, 255, 255, 255 };
}

Texture::Texture(const std::string & text, const std::string & fontpath, int size, SDL_Color color)
	: mGraphics(Graphics::Instance())
{
	mPos = { 0, 0 };
	mRotation = 0.0f;
	mScaleX = 1.0f;
	mScaleY = 1.0f;

	mTexture = AssetManager::Instance().GetText(text, fontpath, size, { 255, 255, 255 });
	SDL_QueryTexture(mTexture.get(), nullptr, nullptr, &mWidth, &mHeight);
	SDL_SetTextureBlendMode(mTexture.get(), SDL_BLENDMODE_BLEND);

	mClipped = false;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;

	mFlip = SDL_FLIP_NONE;
	mColor = color;
}

Texture::~Texture()
{
}

void Texture::Pos(Point pos)
{
	mPos = pos;
}

Point Texture::Pos() const
{
	return mPos;
}

void Texture::Rotation(float rotation)
{
	mRotation = rotation;

	if (mRotation > 360.0f)
		mRotation -= 360.0f;

	if (mRotation < 0.0f)
		mRotation += 360.0f;
}

float Texture::Rotation() const
{
	return mRotation;
}

void Texture::Scale(float scaleX, float scaleY)
{
	mScaleX = scaleX;
	mScaleY = scaleY;
}

float Texture::ScaleX() const
{
	return mScaleX;
}

float Texture::ScaleY() const
{
	return mScaleY;
}

void Texture::Rotate(float amount)
{
	mRotation += amount;

	if (mRotation > 360.0f)
		mRotation -= 360.0f;

	if (mRotation < 0.0f)
		mRotation += 360.0f;
}

float Texture::Width() const
{
	float scaledWidth = mWidth;
	scaledWidth *= mScaleY;

	return scaledWidth;
}

float Texture::Height() const
{
	float scaledHeight = mHeight;
	scaledHeight *= mScaleY;

	return scaledHeight;
}

void Texture::Flip(SDL_RendererFlip flip)
{
	mFlip = flip;
}

void Texture::Color(SDL_Color color)
{
	mColor = color;
}

SDL_Color Texture::Color() const
{
	return mColor;
}

void Texture::Render(bool ignoreCamera)
{
	mRenderRect.x = (int)(mPos.tileX - mWidth * mScaleX * 0.5f);
	mRenderRect.y = (int)(mPos.tileY - mHeight * mScaleY * 0.5f);

	mRenderRect.w = (int)(mWidth * mScaleX);
	mRenderRect.h = (int)(mHeight * mScaleY);

	mGraphics.DrawTexture(mTexture, (mClipped) ? &mClipRect : nullptr, &mRenderRect, mRotation, mFlip, ignoreCamera);

	SDL_SetTextureColorMod(mTexture.get(), 255, 255, 255);
}