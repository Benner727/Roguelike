#ifndef INVENTORY_H
#define INVENTORY_H

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
	void Add(Item* item);
	Item* Remove(int index);

	Item* GetIndex(int index);

	int Size() const { return mItems.size(); }
	bool Full() const { return Size() == MAX_SIZE; }
};

#endif