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
