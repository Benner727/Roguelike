#include "Inventory.h"



Inventory::Inventory()
{
}


Inventory::~Inventory()
{
	for (auto& item : mItems)
		delete item;
}

void Inventory::Add(Item* item)
{
	mItems.push_back(item);
}

Item* Inventory::Remove(int index)
{
	Item* item = mItems[index];
	mItems.erase(mItems.begin() + index);

	return item;
}

Item* Inventory::GetIndex(int index)
{
	if (index < 0 || index >= mItems.size())
		return nullptr;

	return mItems[index];
}

void Inventory::_DrawBackground()
{
	SDL_Color color = { 0, 0, 0, 125 };
	for (int y = 0; y < Graphics::SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < Graphics::SCREEN_WIDTH; x++)
		{
			Graphics::Instance().DrawPixel(x, y, color);
		}
	}
}

bool Edge(int check_x, int check_y, int x, int y, int size)
{
	return check_x == x + size || check_x == x || check_y == y || check_y == y - size;
}

void Inventory::_DrawInventoryBackground()
{
	for (int j = 0; j < Graphics::SCREEN_HEIGHT; j++)
	{
		for (int i = 0; i < Graphics::SCREEN_WIDTH / 2 + PADDING; i++)
		{
			Graphics::Instance().DrawPixel(i, Graphics::SCREEN_HEIGHT - j, brown);
		}
	}
}

void Inventory::_DrawInventoryGrid()
{
	const int gridHeight = INVENTORY_HEIGHT;
	const int gridWidth = INVENTORY_WIDTH;
	const int gridSize = gridWidth / ITEMS_PER_ROW;

	int x;
	int y;
	int row = 0;

	for (int block = 0; block < MAX_SIZE; block++)
	{
		if (block % ITEMS_PER_ROW == 0) row += 1;

		x = PADDING + (block % ITEMS_PER_ROW) * gridSize;
		y = gridHeight - gridSize * row;

		Item* item = GetIndex(block);
		if (item)
		{
			item->Draw(x, y);
		}

		for (int pixel = 0; pixel <= gridSize; pixel++)
		{
			for (int column = 0; column <= gridSize; column++)
			{
				Graphics::Instance().DrawPixel(x + pixel, y + column, gray);
			}

			Graphics::Instance().DrawPixel(x + pixel, y, white);
			Graphics::Instance().DrawPixel(x, y + pixel, white);
			Graphics::Instance().DrawPixel(x + gridSize - pixel, y + gridSize, white);
			Graphics::Instance().DrawPixel(x + gridSize, y + gridSize - pixel, white);
		}
	}
}

void Inventory::Draw()
{
	if (mOpen)
	{
		_DrawBackground();
		_DrawInventoryBackground();
		_DrawInventoryGrid();
	}
}

void Inventory::Toggle()
{
	mOpen = !mOpen;
}