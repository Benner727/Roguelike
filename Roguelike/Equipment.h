#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Weapon.h"
#include "Armor.h"

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

	int Damage() const;
	int Strength() const;
	int Agility() const;
	int Intellect() const;
	int Spirit() const;
	int Stamina() const;
	int Defense() const;
	int Resistance() const;
};

#endif