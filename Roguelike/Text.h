#ifndef TEXT_H
#define TEXT_H

#include <vector>

#include "Sprite.h"

struct Glyph
{
	std::shared_ptr<SDL_Texture> mTexture;
	SDL_Rect mRenderRect;
};

class Text
{
public:
	Text(const std::string& message, int size, SDL_Color color);
	~Text();

private:
	static constexpr const char* FONT_PATH = "Symbola_hint.ttf";

	std::vector<Glyph> mGlyphs;

	Graphics& mGraphics;

	SDL_Color mColor;

public:
	void Draw(int x, int y, bool ignoreCamera = false);
};

#endif