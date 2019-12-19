#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include "Graphics.h"

#include <vector>

class Inventory
{
public:
	Inventory();
	~Inventory();

private:
	static const int MAX_SIZE = 10;
	
	const int PADDING = 20;
	const int ITEMS_PER_ROW = 5;
	const int INVENTORY_HEIGHT = Graphics::SCREEN_HEIGHT - 2 * PADDING;
	const int INVENTORY_WIDTH = (Graphics::SCREEN_WIDTH - 2 * PADDING) / 2;

	const SDL_Color white = { 255, 255, 255, 255 };
	const SDL_Color gray = { 100, 100, 100, 100 };
	const SDL_Color brown = { 115, 87, 63, 255 };

	bool mOpen = false;
	std::vector<Item*> mItems;

	void _DrawBackground();
	void _DrawInventoryBackground();
	void _DrawInventoryGrid();
	void _DrawInventoryItems();

public:
	void Add(Item* item);
	Item* Remove(int index);

	Item* GetIndex(int index);

	int Size() const { return mItems.size(); }
	bool Full() const { return Size() == MAX_SIZE; }
	bool Open() const { return mOpen; }

	void Toggle();
	void Draw();
};

#endif