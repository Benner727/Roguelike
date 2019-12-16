#pragma once

#include "Equippable.h"

class Equipment
{
public:
	Equipment();
	~Equipment();

private:
	Equippable* mItems[(int)EquipmentSlot::TOTAL_SLOTS];

public:
	void Equip(Equippable* item);
	Equippable* Unequip(EquipmentSlot slot);

	Equippable* GetSlot(EquipmentSlot slot);
};

