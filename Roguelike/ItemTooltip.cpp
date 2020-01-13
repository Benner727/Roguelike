#include "ItemTooltip.h"

ItemTooltip::ItemTooltip(int width, int height)
{
	TOOLTIP_WIDTH = width;
	TOOLTIP_HEIGHT = height;
}

ItemTooltip::ItemTooltip()
{
}

ItemTooltip::~ItemTooltip()
{
}

void ItemTooltip::_DrawBorder(int x, int y)
{
	int min_x = x;
	int max_x = x + TOOLTIP_WIDTH;
	int min_y = y;
	int max_y = y + TOOLTIP_HEIGHT;

	Sprite(0, 16, white).Draw(min_x, min_y, true, 1.f); // top left
	Sprite(2, 16, white).Draw(max_x, min_y, true, 1.f); // top right
	Sprite(0, 18, white).Draw(min_x, max_y, true, 1.f); // bottom left
	Sprite(2, 18, white).Draw(max_x, max_y, true, 1.f); // bottom right

	for (int horizontal = min_x; horizontal < max_x; horizontal++)
	{
		Sprite(1, 16, white).Draw(horizontal + 1, min_y, true, 1.f);
		Sprite(1, 18, white).Draw(horizontal + 1, max_y, true, 1.f);
	}

	for (int vertical = min_y + 1; vertical < max_y; vertical++)
	{
		Sprite(0, 17, white).Draw(min_x, vertical, true, 1.f);
		Sprite(2, 17, white).Draw(max_x, vertical, true, 1.f);
	}
}

void ItemTooltip::_DrawItemInfo(int x, int y)
{
	Equippable* mEquippable = dynamic_cast<Equippable*>(mItem);
	Text(mItem->Name(), 24, white).Draw(x + 2, y + 2, true);
	Text("Tier: " + std::to_string(mEquippable->Tier()), 16, white).Draw(x + 2, y + 5, true);
	Text("Strength: " + std::to_string(mEquippable->Strength()), 16, white).Draw(x + 2, y + 7, true);
	Text("Agility: " + std::to_string(mEquippable->Agility()), 16, white).Draw(x + 2, y + 8, true);
	Text("Intellect: " + std::to_string(mEquippable->Intellect()), 16, white).Draw(x + 2, y + 9, true);
	Text("Spirit: " + std::to_string(mEquippable->Spirit()), 16, white).Draw(x + 2, y + 10, true);
	Text("Stamina: " + std::to_string(mEquippable->Stamina()), 16, white).Draw(x + 2, y + 11, true);
}

void ItemTooltip::Draw(int x, int y)
{
	if (mItem)
	{
		_DrawBorder(x, y);
		_DrawItemInfo(x, y);
	}
}
