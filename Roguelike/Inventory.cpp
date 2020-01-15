#include "Inventory.h"

#include "Sprite.h"


Inventory::Inventory() :
	mSlotDefault(DEFAULT_SLOT.tileX, DEFAULT_SLOT.tileY, white),
	mSlotSelected(SELECTED_SLOT.tileX, SELECTED_SLOT.tileY, white),
	mInventoryBackground("inventory-bg.png")
{
	// to do: remove; this is for demonstration purposes
	std::string itemName = "Cool Helmet";
	mItems.push_back(new Equippable(itemName, Sprite(0, 22, white), EquipmentSlot::head, ItemQuality::poor, 1, 10, 10, 10, 0, 100));

	mTooltip = new ItemTooltip(mItems[0], INVENTORY_WIDTH + 4, INVENTORY_HEIGHT / 2 + 1, { INVENTORY_WIDTH + 1, INVENTORY_HEIGHT / 2 });
	mInventoryBackground.Color({ 0, 0, 0, 255 });
	mInventoryBackground.Pos({ Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2});

	_InitializeSprites();
}

Inventory::~Inventory()
{
	for (auto& item : mItems)
		delete item;
	delete mTooltip;
}

void Inventory::_InitializeSprites()
{
	mBorderSprites.push_back(Sprite(0, 16, white, 0, 0)); // top left
	mBorderSprites.push_back(Sprite(2, 16, white, INVENTORY_WIDTH, 0)); // top right
	mBorderSprites.push_back(Sprite(0, 18, white, 0, INVENTORY_HEIGHT)); // bottom left
	mBorderSprites.push_back(Sprite(2, 18, white, INVENTORY_WIDTH, INVENTORY_HEIGHT)); // bottom right

	for (int horizontal = 1; horizontal < INVENTORY_WIDTH; horizontal++)
	{
		mBorderSprites.push_back(Sprite(1, 16, white, horizontal, 0));
		mBorderSprites.push_back(Sprite(1, 18, white, horizontal, INVENTORY_HEIGHT));
	}

	for (int vertical = 1; vertical < INVENTORY_HEIGHT; ++vertical)
	{
		mBorderSprites.push_back(Sprite(0, 17, white, 0, vertical));
		mBorderSprites.push_back(Sprite(2, 17, white, INVENTORY_WIDTH, vertical));
	}
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
	for (int i = 0; i < mBorderSprites.size(); i++)
	{
		mBorderSprites[i].DrawFixed(true, 1.f);
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

		// draw item slot
		if (mSelected == index)
		{
			mSlotSelected.Draw(x, y, true, ITEM_SCALE, Sprite::TILE_SIZE, Sprite::TILE_SIZE);
		}
		else
		{
			mSlotDefault.Draw(x, y, true, ITEM_SCALE, Sprite::TILE_SIZE, Sprite::TILE_SIZE);
		}
	}
}

void Inventory::_DrawItemInfo()
{
	if (mSelected > -1)
	{
		mTooltip->Draw();
	}
}

void Inventory::Draw()
{
	if (mOpen)
	{
		mInventoryBackground.Render(true);
		_DrawInventoryContainer();
		_DrawInventoryItems();
		_DrawItemInfo();
	}
}
