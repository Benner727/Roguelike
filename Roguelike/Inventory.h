#ifndef INVENTORY_H
#define INVENTORY_H

#include "Equipment.h"
#include "Item.h"
#include "ItemTooltip.h"
#include "MathHelper.h"
#include "Sprite.h"
#include "Texture.h"

#include <vector>

class Inventory
{
public:
	Inventory();
	~Inventory();

private:
	static const int MAX_SIZE = 10;
	static const int ITEM_SCALE = 4.f;

	const int INVENTORY_HEIGHT = (Graphics::SCREEN_HEIGHT / Sprite::TILE_SIZE) - 1;
	const int INVENTORY_WIDTH = (Graphics::SCREEN_WIDTH  / Sprite::TILE_SIZE / 2) - 3;
	const Point DEFAULT_SLOT = Point(23, 26);
	const Point SELECTED_SLOT = Point(19, 24);

	const SDL_Color transparent_black = { 0, 0, 0, 180 };
	const SDL_Color white = { 255, 255, 255, 255 };

	int mSelected = -1;

	ItemTooltip* mTooltip;
	bool mOpen = false;

	std::vector<Item*> mItems;
	std::vector<Sprite> mBorderSprites;
	Sprite mSlotDefault;
	Sprite mSlotSelected;
	Texture mInventoryBackground;

	void _InitializeSprites();
	void _DrawInventoryContainer();
	void _DrawInventoryItems();
	void _DrawItemInfo();

public:
	void Add(Item* item);
	Item* Remove(int index);
	void Select(int MouseX, int MouseY);
	
	Item* GetIndex(int index);
	int Selected() const { return mSelected; }

	int Size() const { return mItems.size(); }
	bool Full() const { return Size() == MAX_SIZE; }
	bool Open() const { return mOpen; }

	void Toggle() { mOpen = !mOpen; }
	void Draw();
};

#endif