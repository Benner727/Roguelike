#ifndef ITEM_H
#define ITEM_H

#include "Sprite.h"

class Item
{
public:
	Item(std::string name, Sprite sprite, bool stackable = false, int amount = 1);
	virtual ~Item();

private:
	std::string mName;
	Sprite mSprite;
	bool mStackable;
	int mAmount;

public:
	std::string Name() const { return mName; }
	bool Stackable() const { return mStackable; }
	int Amount() const { return mAmount; }

	void AddAmount(int amount) { mAmount += amount; }
	void RemoveAmount(int amount) { mAmount -= amount; }

	void Draw(int x, int y, bool ignoreCamera = true, int scale = 1, int offset = 0);
};

#endif