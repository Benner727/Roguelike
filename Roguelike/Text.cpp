#include "Text.h"



Text::Text(const std::string& message, int size, SDL_Color color)
	: mGraphics(Graphics::Instance()), mColor(color)
{
	for (const auto& c : message)
	{
		Glyph glyph;
		glyph.mTexture = AssetManager::Instance().GetText(std::string(1, c), FONT_PATH, size, { 255, 255, 255 });
		SDL_QueryTexture(glyph.mTexture.get(), nullptr, nullptr, &glyph.mRenderRect.w, &glyph.mRenderRect.h);
		
		SDL_SetTextureBlendMode(glyph.mTexture.get(), SDL_BLENDMODE_BLEND);
		
		mGlyphs.push_back(glyph);
	}
}


Text::~Text()
{
}

void Text::Alpha(int alpha)
{
	for (int i = 0; i < mGlyphs.size(); ++i)
		SDL_SetTextureAlphaMod(mGlyphs[i].mTexture.get(), alpha);
}

void Text::Draw(int x, int y, bool ignoreCamera)
{
	int offset = 0;

	for (int i = 0; i < mGlyphs.size(); ++i)
	{
		mGlyphs[i].mRenderRect.x = x * Sprite::TILE_SIZE + offset;
		mGlyphs[i].mRenderRect.y = y * Sprite::TILE_SIZE;

		offset += mGlyphs[i].mRenderRect.w;

		SDL_SetTextureColorMod(mGlyphs[i].mTexture.get(), mColor.r, mColor.g, mColor.b);

		mGraphics.DrawTexture(mGlyphs[i].mTexture, nullptr, &mGlyphs[i].mRenderRect, ignoreCamera);

		SDL_SetTextureColorMod(mGlyphs[i].mTexture.get(), 255, 255, 255);
	}
}