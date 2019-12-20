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

int Equipment::Damage() const
{
	int damage = 0;

	if (Weapon* weapon = dynamic_cast<Weapon*>(mItems[(int)EquipmentSlot::weapon]))
		damage = weapon->Damage();

	return damage;
}

int Equipment::Strength() const
{
	int strength = 0;

	for (int i = 0; i < (int)EquipmentSlot::TOTAL_SLOTS; i++)
	{
		if (mItems[i] != nullptr)
			strength += mItems[i]->Strength();
	}

	return strength;
}

int Equipment::Agility() const
{
	int agility = 0;

	for (int i = 0; i < (int)EquipmentSlot::TOTAL_SLOTS; i++)
	{
		if (mItems[i] != nullptr)
			agility += mItems[i]->Agility();
	}

	return agility;
}

int Equipment::Intellect() const
{
	int intellect = 0;

	for (int i = 0; i < (int)EquipmentSlot::TOTAL_SLOTS; i++)
	{
		if (mItems[i] != nullptr)
			intellect += mItems[i]->Intellect();
	}

	return intellect;
}

int Equipment::Spirit() const
{
	int spirit = 0;

	for (int i = 0; i < (int)EquipmentSlot::TOTAL_SLOTS; i++)
	{
		if (mItems[i] != nullptr)
			spirit += mItems[i]->Spirit();
	}

	return spirit;
}

int Equipment::Stamina() const
{
	int stamina = 0;

	for (int i = 0; i < (int)EquipmentSlot::TOTAL_SLOTS; i++)
	{
		if (mItems[i] != nullptr)
			stamina += mItems[i]->Stamina();
	}

	return stamina;
}

int Equipment::Defense() const
{
	int defense = 0;

	for (int i = 0; i < (int)EquipmentSlot::TOTAL_SLOTS; i++)
	{
		if (Armor* armor = dynamic_cast<Armor*>(mItems[i]))
			defense += armor->Defense();
	}

	return defense;
}

int Equipment::Resistance() const
{
	int resistance = 0;

	for (int i = 0; i < (int)EquipmentSlot::TOTAL_SLOTS; i++)
	{
		if (Armor* armor = dynamic_cast<Armor*>(mItems[i]))
			resistance += armor->Resistance();
	}

	return resistance;
}