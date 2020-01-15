#ifndef ITEM_TOOLTIP_H
#define ITEM_TOOLTIP_H

#include "Equippable.h"
#include "Item.h"
#include "Text.h"
#include "Sprite.h"
#include "MathHelper.h"

class ItemTooltip
{
public:
	ItemTooltip(Item* item, int width, int height, Point pos);
	~ItemTooltip();

private:
	int mWidth;
	int mHeight;
	Point mPos;
	Item* mItem;
	Equippable* mEquippable;

	Text mTitle;
	std::vector<Sprite> mBorderSprites;
	std::vector<Text> mStatsText;
	const SDL_Color white = { 255, 255, 255, 255 };

	void _InitializeSprites();
	void _InitializeTexts();
	void _DrawBorder();
	void _DrawItemInfo();
	
public:
	void Pos(Point pos);
	void SetItem(Item* item) { mItem = item; }
	void Draw();
};

#endif ITEM_TOOLTIP_H
