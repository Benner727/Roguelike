#ifndef INVENTORY_H
#define INVENTORY_H

#include "Equipment.h"
#include "Item.h"
#include "ItemTooltip.h"
#include "Sprite.h"

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

	const SDL_Color transparent_black = { 0, 0, 0, 180 };
	const SDL_Color white = { 255, 255, 255, 255 };
	const SDL_Color gray = { 100, 100, 100, 100 };
	const SDL_Color brown = { 115, 87, 63, 255 };
	const std::tuple<int, int> DEFAULT_SLOT = std::make_tuple(23, 26);
	const std::tuple<int, int> SELECTED_SLOT = std::make_tuple(19, 24);

	int mSelected = -1;

	ItemTooltip* mTooltip;
	bool mOpen = false;

	std::string itemName = "Cool Helmet";
	Item* mItem = new Equippable(itemName, Sprite(0, 22, white), EquipmentSlot::head, ItemQuality::poor, 1, 10, 10, 10, 0, 100);
	std::vector<Item*> mItems = { mItem };

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