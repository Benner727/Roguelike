#pragma once

#include "Item.h"

#include <vector>

class Inventory
{
public:
	Inventory();
	~Inventory();

private:
	static const int MAX_SIZE = 10;

	std::vector<Item*> mItems;

public:
	void PickUp(Item* item);
	Item* Drop(int index);

	Item* GetIndex(int index);
	int Size() const;
};