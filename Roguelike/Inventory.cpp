#include "Inventory.h"

#include "Sprite.h"

Inventory::Inventory()
{
	mTooltip = new ItemTooltip(INVENTORY_WIDTH + 4, INVENTORY_HEIGHT / 2 + 1);
}


Inventory::~Inventory()
{
	for (auto& item : mItems)
		delete item;
	delete mTooltip;
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

void Inventory::_DrawInventoryContainer()
{
	for (int y = 0; y < Graphics::SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x < Graphics::SCREEN_WIDTH; x++)
		{
			Graphics::Instance().DrawPixel(x, y, transparent_black);
		}
	}

	Sprite(0, 16, white).Draw(0, 0, true, 1.f); // top left
	Sprite(2, 16, white).Draw(INVENTORY_WIDTH, 0, true, 1.f); // top right
	Sprite(0, 18, white).Draw(0, INVENTORY_HEIGHT, true, 1.f); // bottom left
	Sprite(2, 18, white).Draw(INVENTORY_WIDTH, INVENTORY_HEIGHT, true, 1.f); // bottom right

	for (int horizontal = 1; horizontal < INVENTORY_WIDTH; horizontal++)
	{
		Sprite(1, 16, white).Draw(horizontal, 0, true, 1.f);
		Sprite(1, 18, white).Draw(horizontal, INVENTORY_HEIGHT, true, 1.f);
	}

	for (int vertical = 1; vertical < INVENTORY_HEIGHT; ++vertical)
	{
		Sprite(0, 17, white).Draw(0, vertical, true, 1.f);
		Sprite(2, 17, white).Draw(INVENTORY_WIDTH, vertical, true, 1.f);
	}
}

bool Edge(int check_x, int check_y, int x, int y, int size)
{
	return check_x == x + size || check_x == x || check_y == y || check_y == y - size;
}

void Inventory::Select(int MouseX, int MouseY)
{
	int x = (MouseX - 1) / ITEM_SCALE;
	int y = (MouseY - 1) / ITEM_SCALE - 5;
	int items_per_row = 5;
	int index = x + y * items_per_row;
	bool is_slot = index >= 0 && index < MAX_SIZE;
	
	if (is_slot && index != mSelected)
	{
		mSelected = index;
		if (GetIndex(mSelected))
		{
			mTooltip->SetItem(GetIndex(mSelected));
		}
		else
		{
			mTooltip->SetItem(nullptr);
		}
	}
	else if (!is_slot)
	{
		mSelected = -1;
		mTooltip->SetItem(nullptr);
	}
}


void Inventory::_DrawInventoryItems()
{
	int y = 5;
	int x = -1;

	for (int index = 0; index < MAX_SIZE; index++)
	{
		Item* item = GetIndex(index);
		if ((x + 2) * ITEM_SCALE >= INVENTORY_WIDTH)
		{
			y++;
			x = 0;
		}
		else
		{
			x++;
		}

		if (item)
		{
			item->Draw(x, y, true, ITEM_SCALE / 2, 1);
		}

		int xSprite = (mSelected == index) ? std::get<0>(SELECTED_SLOT) : std::get<0>(DEFAULT_SLOT);
		int ySprite = (mSelected == index) ? std::get<1>(SELECTED_SLOT) : std::get<1>(DEFAULT_SLOT);

		// draw item slot
		Sprite(xSprite, ySprite, white).Draw(x, y, true, ITEM_SCALE, Sprite::TILE_SIZE, Sprite::TILE_SIZE);
	}
}

void Inventory::_DrawItemInfo()
{
	if (mSelected > -1)
	{
		mTooltip->Draw(INVENTORY_WIDTH + 1, INVENTORY_HEIGHT / 2);
	}
}

void Inventory::Draw()
{
	if (mOpen)
	{
		_DrawInventoryContainer();
		_DrawInventoryItems();
		_DrawItemInfo();
	}
}
