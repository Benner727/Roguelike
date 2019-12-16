#include "Player.h"

#include "Weapon.h"
#include "Armor.h"

Player::Player(Point pos)
	: Entity(pos, Sprite(SPRITE_TILE_X, SPRITE_TILE_Y, { 255, 255, 255 }))
{
}

Player::Player(int x, int y)
	: Player(Point(x, y))
{
}

Player::~Player()
{
}

void Player::PickUp(Item* item)
{
	mInventory.Add(item);
}

Item* Player::Drop(int index)
{
	return mInventory.Remove(index);
}

bool Player::CanEquip(int index)
{
	if (Weapon* weapon = dynamic_cast<Weapon*>(mInventory.GetIndex(index)))
	{
		if (mInventory.Full() && weapon->TwoHanded())
		{
			Item* shield = mEquipment.Unequip(EquipmentSlot::shield);
			if (shield != nullptr)
				return false;
		}
	}
	else if (Armor* armor = dynamic_cast<Armor*>(mInventory.GetIndex(index)))
	{
		if (mInventory.Full() && armor->Slot() == EquipmentSlot::shield)
		{
			if (mEquipment.GetSlot(EquipmentSlot::weapon) != nullptr)
				return false;
		}
	}

	return true;
}

void Player::Equip(int index)
{
	if (Equippable* gear = dynamic_cast<Equippable*>(mInventory.GetIndex(index)))
	{
		bool unequipWeapon = false;
		bool unequipShield = false;

		if (Armor* armor = dynamic_cast<Armor*>(gear))
		{
			if (gear->Slot() == EquipmentSlot::shield)
			{
				if (Weapon* weapon = dynamic_cast<Weapon*>(mEquipment.GetSlot(EquipmentSlot::weapon)))
					unequipWeapon = weapon->TwoHanded();
			}
		}
		else if (Weapon* weapon = dynamic_cast<Weapon*>(gear))
			unequipShield = weapon->TwoHanded();

		Item* unequippedSlot = mEquipment.Unequip(gear->Slot());
		if (unequippedSlot != nullptr)
			mInventory.Add(unequippedSlot);

		mInventory.Remove(index);
		mEquipment.Equip(gear);

		if (unequipWeapon)
		{
			Item* weapon = mEquipment.Unequip(EquipmentSlot::weapon);
			if (weapon != nullptr)
				mInventory.Add(weapon);
		}

		if (unequipShield)
		{
			Item* shield = mEquipment.Unequip(EquipmentSlot::shield);
			if (shield != nullptr)
				mInventory.Add(shield);
		}
	}
}

void Player::Unequip(int slot)
{
	Item* unequippedSlot = mEquipment.Unequip(static_cast<EquipmentSlot>(slot));

	if (unequippedSlot != nullptr)
		mInventory.Add(unequippedSlot);
}
