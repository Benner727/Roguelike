#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Equipment.h"
#include "Inventory.h"

class Player : public Entity
{
public:
	Player(Point pos);
	Player(int x = 0, int y = 0);
	~Player();

private:
	static const int SPRITE_TILE_X = 26;
	static const int SPRITE_TILE_Y = 0;

	Inventory mInventory;
	Equipment mEquipment;

	void CalculateStats();

public:
	bool InventoryFull() const { return mInventory.Full(); }
	bool InventoryOpen() const { return mInventory.Open(); }
	void ToggleInventory() { mInventory.Toggle(); }
	void PickUp(Item* item);
	Item* Drop(int index);

	bool CanEquip(int index);
	void Equip(int index);
	void Unequip(int slot);

	void Draw();
};

#endif