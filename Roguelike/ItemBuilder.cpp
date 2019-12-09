#include "ItemBuilder.h"



std::vector<ItemBuilder::WeaponTemplate> ItemBuilder::mWeaponTemplates =
{
	//Melee
	WeaponTemplate({"Bronze", "Iron", "Steel"}, {"Sword"}, CombatType::melee, 2.5f, 1, false, true, false, false, false),
	WeaponTemplate({"Bronze", "Iron", "Steel"}, {"Mace"}, CombatType::melee, 2.5f, 1, false, true, false, false, false),
	WeaponTemplate({"Bronze", "Iron", "Steel"}, {"Greataxe"}, CombatType::melee, 3.5f, 1, true, true, false, false, false),
	WeaponTemplate({"Bronze", "Iron", "Steel"}, {"Maul"}, CombatType::melee, 3.5f, 1, true, true, false, false, true),

	//Ranged
	WeaponTemplate({"Wood"}, {"Recurve Bow"}, CombatType::ranged, 3.5f, 6, true, false, true, false, true),
	WeaponTemplate({"Wood"}, {"Long Bow"}, CombatType::ranged, 3.0f, 8, true, false, true, false, true),
	WeaponTemplate({"Wood"}, {"Crossbow"}, CombatType::ranged, 2.5f, 4, false, false, true, false, true),

	//Magic
	WeaponTemplate({"Wood"}, {"Staff"}, CombatType::magic, 3.5f, 7, true, false, false, true, true),
	WeaponTemplate({"Wood"}, {"Wand"}, CombatType::magic, 2.5f, 5, false, false, false, true, true),
};

std::vector<ItemBuilder::ArmorTemplate> ItemBuilder::mArmorTemplates =
{
	//Melee
	ArmorTemplate(EquipmentSlot::head, {"Bronze", "Iron", "Steel"}, {"Faceguard", "Helmet"}, 0.35f, true, false, false, true),
	ArmorTemplate(EquipmentSlot::chest, {"Bronze", "Iron", "Steel"}, {"Hauberk", "Platebody"}, 1.0f, true, false, false, true),
	ArmorTemplate(EquipmentSlot::legs, {"Bronze", "Iron", "Steel"}, {"Tassets", "Platelegs"}, 0.85f, true, false, false, true),
	ArmorTemplate(EquipmentSlot::gloves, {"Bronze", "Iron", "Steel"}, {"Gauntlets", "Gloves"}, 0.25f, true, false, false, true),
	ArmorTemplate(EquipmentSlot::boots, {"Bronze", "Iron", "Steel"}, {"Greaves", "Boots"}, 0.25f, true, false, false, true),

	//Ranged
	ArmorTemplate(EquipmentSlot::head, {"Leather", "Hide", "Chain"}, {"Cowl", "Coif"}, 0.35f, false, true, true, false),
	ArmorTemplate(EquipmentSlot::chest, {"Leather", "Hide", "Chain"}, {"Tunic", "Body"}, 1.0f, false, true, true, false),
	ArmorTemplate(EquipmentSlot::legs, {"Leather", "Hide", "Chain"}, {"Chaps", "Pants"}, 0.85f, false, true, true, false),
	ArmorTemplate(EquipmentSlot::gloves, {"Leather", "Hide", "Chain"}, {"Vambraces", "Gloves"}, 0.25f, false, true, true, false),
	ArmorTemplate(EquipmentSlot::boots, {"Leather", "Hide", "Chain"}, {"Shoes", "Boots"}, 0.25f, false, true, true, false),

	//Magic
	ArmorTemplate(EquipmentSlot::head, {"Cloth", "Silk"}, {"Hood", "Hat"}, 0.35f, false, false, true, true),
	ArmorTemplate(EquipmentSlot::chest, {"Cloth", "Silk"}, {"Robe", "Shirt"}, 1.0f, false, false, true, true),
	ArmorTemplate(EquipmentSlot::legs, {"Cloth", "Silk"}, {"Skirt", "Leggings"}, 0.85f, false, false, true, true),
	ArmorTemplate(EquipmentSlot::gloves, {"Cloth", "Silk"}, {"Wraps", "Gloves"}, 0.25f, false, false, true, true),
	ArmorTemplate(EquipmentSlot::boots, {"Cloth", "Silk"}, {"Socks", "Slippers"}, 0.25f, false, false, true, true),

	//Offhand
	ArmorTemplate(EquipmentSlot::cloak, {"Wood"}, {"Buckler"}, 0.35f, true, true, false, false),
	ArmorTemplate(EquipmentSlot::cloak, {"Bronze", "Iron", "Steel" }, {"Shield"}, 0.55f, true, false, false, true),
	ArmorTemplate(EquipmentSlot::cloak, {"Green", "Pink"}, {"Ward"}, 0.15f, false, false, true, true),
	ArmorTemplate(EquipmentSlot::cloak, {"Flame", "Earth", "Wind"}, {"Totem"}, 0.15f, false, false, true, true),

	//Misc
	ArmorTemplate(EquipmentSlot::cloak, {"Fur", "Scale"}, {"Cape", "Cloak"}, 0.15f, true, true, true, true),
	ArmorTemplate(EquipmentSlot::amulet, {"Brass", "Silver", "Gold"}, {"Amulet", "Necklace"}, 0.0f, true, true, true, true),
	ArmorTemplate(EquipmentSlot::ring, {"Brass", "Silver", "Gold"}, {"Ring", "Heirloom"}, 0.0f, true, true, true, true)
};

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
