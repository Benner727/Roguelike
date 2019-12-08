#include "ItemBuilder.h"



ItemBuilder::ItemBuilder()
	: mRNG(RNG(time(nullptr)))
{
}


ItemBuilder::~ItemBuilder()
{
}

ItemQuality ItemBuilder::RollQuality()
{
	int roll = mRNG.RandomNumber(1, 63);

	if (roll < 2)
		return ItemQuality::legendary;
	else if (roll < 4)
		return ItemQuality::epic;
	else if (roll < 8)
		return ItemQuality::rare;
	else if (roll < 16)
		return ItemQuality::uncommon;
	else if (roll < 32)
		return ItemQuality::common;
	else if (roll < 64)
		return ItemQuality::poor;
}

EquipmentSlot ItemBuilder::RollSlot(bool includeWeapon)
{
	int slotRoll = mRNG.RandomNumber(includeWeapon ? 0 : 1, (int)EquipmentSlot::TOTAL_SLOTS - 1);

	return static_cast<EquipmentSlot>(slotRoll);
}

int ItemBuilder::RollStat(int tier, ItemQuality quality)
{
	int statRoll = mRNG.RandomNumber(1 + (int)quality, 3 + (int)quality);
	statRoll *= (1.0f + (float)tier / 4.0f);

	return statRoll;
}

int ItemBuilder::RollDamage(int tier)
{
	int damage = (1 + ((float)tier / 10.0f) * 2) * 60;
	damage *= ((float)mRNG.RandomNumber(85, 100) / 100.0f);

	return damage;
}

int ItemBuilder::RollArmorValue(int tier)
{
	int armorValue = (1 + ((float)tier / 5.0f) * 2) * 40;
	armorValue *= ((float)mRNG.RandomNumber(85, 100) / 100.0f);

	return armorValue;
}

Weapon * ItemBuilder::GetRandomWeapon(int tier)
{
	return nullptr;
}

Armor * ItemBuilder::GetRandomArmor(int tier)
{
	return nullptr;
}

Equippable * ItemBuilder::GetRandomEquippable(int tier)
{
	return nullptr;
}
