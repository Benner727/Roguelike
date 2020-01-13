#ifndef ITEM_TOOLTIP_H
#define ITEM_TOOLTIP_H

#include "Equippable.h"
#include "Item.h"
#include "Text.h"

class ItemTooltip
{
public:
	ItemTooltip(int width, int height);
	ItemTooltip();
	~ItemTooltip();

private:
	int TOOLTIP_WIDTH;
	int TOOLTIP_HEIGHT;
	Item* mItem;

	const SDL_Color white = { 255, 255, 255, 255 };

	void _DrawBorder(int x, int y);
	void _DrawItemInfo(int x, int y);
	
public:
	void SetItem(Item* item) { mItem = item; }
	void Draw(int x, int y);
};

#endif ITEM_TOOLTIP_H
