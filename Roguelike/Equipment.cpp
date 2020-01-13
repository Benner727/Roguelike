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

void Equipment::_DrawEquippedItems()
{
	Equippable* mEquippable;
	int x;
	int y;
	for (int slot = 0; slot < (int)EquipmentSlot::TOTAL_SLOTS; slot++)
	{
		int x;
		int y;
		mEquippable = mItems[slot];

		switch ((EquipmentSlot) slot)
		{
		case EquipmentSlot::head:
			x = 2; y = 0;
			break;
		case EquipmentSlot::chest:
			x = 2; y = 1;
			break;
		case EquipmentSlot::legs:
			x = 2; y = 2;
			break;
		case EquipmentSlot::boots:
			x = 2; y = 3;
			break;
		case EquipmentSlot::cloak:
			x = 3; y = 1;
			break;
		case EquipmentSlot::gloves:
			x = 1; y = 1;
			break;
		case EquipmentSlot::ring:
			x = 0; y = 1;
			break;
		case EquipmentSlot::amulet:
			x = 3; y = 0;
			break;
		case EquipmentSlot::weapon:
			x = 1; y = 2;
			break;
		case EquipmentSlot::shield:
			x = 3; y = 2;
			break;
		}

		Sprite(std::get<0>(DEFAULT_SLOT), std::get<1>(DEFAULT_SLOT), white).Draw(x, y, true, ITEM_SCALE, Sprite::TILE_SIZE, Sprite::TILE_SIZE);
		if (mEquippable) mEquippable->Draw(x, y, true, ITEM_SCALE / 2, 1);
	}
}

void Equipment::Draw()
{
	if (mOpen)
	{
		_DrawEquippedItems();
	}
}