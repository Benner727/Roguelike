#include "Inventory.h"



Inventory::Inventory()
{
}


Inventory::~Inventory()
{
	for (auto& item : mItems)
		delete item;
}

void Inventory::PickUp(Item* item)
{
	mItems.push_back(item);
}

Item* Inventory::Drop(int index)
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

int Inventory::Size() const
{
	return mItems.size();
}
