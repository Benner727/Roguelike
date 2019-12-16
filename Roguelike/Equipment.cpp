#include "Equipment.h"



Equipment::Equipment()
{
	for (int i = 0; i < (int)EquipmentSlot::TOTAL_SLOTS; i++)
		mItems[i] = nullptr;
}


Equipment::~Equipment()
{
	for (int i = 0; i < (int)EquipmentSlot::TOTAL_SLOTS; i++)
		delete mItems[i];
}

void Equipment::Equip(Equippable* item)
{
	mItems[(int)item->Slot()] = item;
}

Equippable* Equipment::Unequip(EquipmentSlot slot)
{
	Equippable* item = mItems[(int)slot];
	mItems[(int)slot] = nullptr;
	
	return item;
}

Equippable* Equipment::GetSlot(EquipmentSlot slot)
{
	return mItems[(int)slot];
}
