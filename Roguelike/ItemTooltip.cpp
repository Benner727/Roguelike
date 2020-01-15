#include "ItemTooltip.h"

ItemTooltip::ItemTooltip(Item* item, int width, int height, Point pos) :
	mTitle(Text(item->Name(), 24, white))
{
	mWidth = width;
	mHeight = height;
	mItem = item;
	mPos = pos;
	mEquippable = dynamic_cast<Equippable*>(mItem);

	_InitializeSprites();
	_InitializeTexts();
}


ItemTooltip::~ItemTooltip()
{
}

void ItemTooltip::_InitializeSprites()
{
	int min_x = mPos.tileX;
	int max_x = min_x + mWidth;
	int min_y = mPos.tileY;
	int max_y = min_y + mHeight;

	mBorderSprites.push_back(Sprite(0, 16, white, min_x, min_y));
	mBorderSprites.push_back(Sprite(2, 16, white, max_x, min_y));
	mBorderSprites.push_back(Sprite(0, 18, white, min_x, max_y));
	mBorderSprites.push_back(Sprite(2, 18, white, max_x, max_y));

	for (int horizontal = min_x; horizontal < max_x; horizontal++)
	{
		mBorderSprites.push_back(Sprite(1, 16, white, horizontal + 1, min_y));
		mBorderSprites.push_back(Sprite(1, 18, white, horizontal + 1, max_y));
	}

	for (int vertical = min_y + 1; vertical < max_y; vertical++)
	{
		mBorderSprites.push_back(Sprite(0, 17, white, min_x, vertical));
		mBorderSprites.push_back(Sprite(2, 17, white, max_x, vertical));
	}
}

void ItemTooltip::_InitializeTexts()
{
	mStatsText.push_back(Text("Tier: " + std::to_string(mEquippable->Tier()), 16, white));
	mStatsText.push_back(Text("Strength: " + std::to_string(mEquippable->Strength()), 16, white));
	mStatsText.push_back(Text("Agility: " + std::to_string(mEquippable->Agility()), 16, white));
	mStatsText.push_back(Text("Intellect: " + std::to_string(mEquippable->Intellect()), 16, white));
	mStatsText.push_back(Text("Spirit: " + std::to_string(mEquippable->Spirit()), 16, white));
	mStatsText.push_back(Text("Stamina: " + std::to_string(mEquippable->Stamina()), 16, white));
}

void ItemTooltip::_DrawBorder()
{
	for (int i = 0; i < mBorderSprites.size(); i++)
	{
		mBorderSprites[i].DrawFixed(true, 1.f);
	}
}

void ItemTooltip::_DrawItemInfo()
{
	mTitle.Draw(mPos.tileX + 2, mPos.tileY + 2, true);

	int y_offset = 5;
	for (int i = 0; i < mStatsText.size(); i++)
	{
		mStatsText[i].Draw(mPos.tileX + 2, mPos.tileY + y_offset, true);
		y_offset += 1;
	}
}

void ItemTooltip::Pos(Point pos)
{
	mPos = pos;
	mBorderSprites.clear();
	mStatsText.clear();

	_InitializeSprites();
	_InitializeTexts();
}

void ItemTooltip::Draw()
{
	if (mItem)
	{
		_DrawBorder();
		_DrawItemInfo();
	}
}
