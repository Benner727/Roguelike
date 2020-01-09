#ifndef TEXTURE_H
#define TEXTURE_H

#include "AssetManager.h"
#include "MathHelper.h"

class Texture
{
private:
	Point mPos;
	float mRotation;
	float mScaleX;
	float mScaleY;

	std::shared_ptr<SDL_Texture> mTexture;

	Graphics& mGraphics;

	int mWidth;
	int mHeight;

	bool mClipped;
	SDL_Rect mRenderRect;
	SDL_Rect mClipRect;

	SDL_RendererFlip mFlip;
	SDL_Color mColor;

public:
	Texture(const std::string& filename);
	Texture(const std::string& filename, int x, int y, int w, int h);
	Texture(const std::string& text, const std::string& fontpath, int size, SDL_Color color);
	~Texture();

	void Pos(Point pos);
	Point Pos() const;

	void Rotation(float rotation);
	float Rotation() const;

	void Scale(float scaleX, float scaleY);
	float ScaleX() const;
	float ScaleY() const;

	void Rotate(float amount);

	float Width() const;
	float Height() const;

	void Flip(SDL_RendererFlip flip);
	void Color(SDL_Color color);
	SDL_Color Color() const;

	void Render(bool ignoreCamera = false);
};

#endif