#include "ItemBuilder.h"



std::vector<ItemBuilder::WeaponTemplate> ItemBuilder::mWeaponTemplates =
{
	//Melee
	WeaponTemplate({"Bronze", "Iron", "Steel"}, {"Sword"}, CombatType::melee, 2.5f, 1, false, true, false, false, false),
	WeaponTemplate({"Bronze", "Iron", "Steel"}, {"Mace"}, CombatType::melee, 2.5f, 1, false, true, false, false, false),
	WeaponTemplate({"Bronze", "Iron", "Steel"}, {"Greataxe"}, CombatType::melee, 3.5f, 1, true, true, false, false, false),
	WeaponTemplate({"Bronze", "Iron", "Steel"}, {"Maul"}, CombatType::melee, 3.5f, 1, true, true, false, false, true),

	//Ranged
	WeaponTemplate({"Wood"}, {"Recurve Bow"}, CombatType::ranged, 3.5f, 6, true, false, true, false, false),
	WeaponTemplate({"Wood"}, {"Long Bow"}, CombatType::ranged, 3.0f, 8, true, false, true, false, false),
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
	ArmorTemplate(EquipmentSlot::head, {"Leather", "Hide", "Chain"}, {"Cowl", "Coif"}, 0.25f, false, true, true, false),
	ArmorTemplate(EquipmentSlot::chest, {"Leather", "Hide", "Chain"}, {"Tunic", "Body"}, 0.9f, false, true, true, false),
	ArmorTemplate(EquipmentSlot::legs, {"Leather", "Hide", "Chain"}, {"Chaps", "Pants"}, 0.75f, false, true, true, false),
	ArmorTemplate(EquipmentSlot::gloves, {"Leather", "Hide", "Chain"}, {"Vambraces", "Gloves"}, 0.15f, false, true, true, false),
	ArmorTemplate(EquipmentSlot::boots, {"Leather", "Hide", "Chain"}, {"Shoes", "Boots"}, 0.15f, false, true, true, false),

	//Magic
	ArmorTemplate(EquipmentSlot::head, {"Cloth", "Silk"}, {"Hood", "Hat"}, 0.20f, false, false, true, true),
	ArmorTemplate(EquipmentSlot::chest, {"Cloth", "Silk"}, {"Robe", "Shirt"}, 0.85f, false, false, true, true),
	ArmorTemplate(EquipmentSlot::legs, {"Cloth", "Silk"}, {"Skirt", "Leggings"}, 0.70f, false, false, true, true),
	ArmorTemplate(EquipmentSlot::gloves, {"Cloth", "Silk"}, {"Wraps", "Gloves"}, 0.10f, false, false, true, true),
	ArmorTemplate(EquipmentSlot::boots, {"Cloth", "Silk"}, {"Socks", "Slippers"}, 0.10f, false, false, true, true),

	//Offhand
	ArmorTemplate(EquipmentSlot::cloak, {"Wood"}, {"Buckler"}, 0.35f, true, true, false, false),
	ArmorTemplate(EquipmentSlot::cloak, {"Bronze", "Iron", "Steel" }, {"Shield"}, 0.50f, true, false, false, true),
	ArmorTemplate(EquipmentSlot::cloak, {"Green", "Pink"}, {"Ward"}, 0.10f, false, false, true, true),
	ArmorTemplate(EquipmentSlot::cloak, {"Flame", "Earth", "Wind"}, {"Totem"}, 0.05f, false, false, true, true),

	//Misc
	ArmorTemplate(EquipmentSlot::cloak, {"Fur", "Scale"}, {"Cape", "Cloak"}, 0.10f, true, true, true, true),
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
	WeaponTemplate itemTemplate = mWeaponTemplates[mRNG.RandomNumber(0, mWeaponTemplates.size() - 1)];

	std::string material = itemTemplate.material[mRNG.RandomNumber(0, itemTemplate.material.size() - 1)];
	std::string piece = itemTemplate.piece[mRNG.RandomNumber(0, itemTemplate.piece.size() - 1)];
	std::string name = material + " " + piece;

	ItemQuality quality = RollQuality();

	int stats[4] = { 0, 0, 0, 0 };
	std::vector<int> possibleStats;

	if (itemTemplate.strength)
		possibleStats.push_back(0);
	if (itemTemplate.agility)
		possibleStats.push_back(1);
	if (itemTemplate.intellect)
		possibleStats.push_back(2);
	if (itemTemplate.spirit)
		possibleStats.push_back(3);

	int statPos = mRNG.RandomNumber(0, possibleStats.size() - 1);
	int statIndex = possibleStats[statPos];
	stats[statIndex] = RollStat(tier, quality);

	if (possibleStats.size() > 1 && mRNG.RandomNumber(0, 1) == 0)
	{
		stats[statIndex] = ceil((float)stats[statIndex] * 0.66f);
		possibleStats.erase(possibleStats.begin() + statPos);

		statIndex = possibleStats[mRNG.RandomNumber(0, possibleStats.size() - 1)];
		stats[statIndex] = ceil((float)RollStat(tier, quality) * 0.66f);
	}

	int stamina = 0;

	int damage = RollDamage(tier) * itemTemplate.damageModifier;

	Weapon* weapon = new Weapon(name, Sprite(0, 0, { 255, 255, 255 }), quality, tier,
		stats[0], stats[1], stats[2], stats[3], stamina, damage,
		itemTemplate.type, itemTemplate.range, itemTemplate.twoHanded);

	return weapon;
}

Armor * ItemBuilder::GetRandomArmor(int tier)
{
	ArmorTemplate itemTemplate = mArmorTemplates[mRNG.RandomNumber(0, mWeaponTemplates.size() - 1)];

	std::string material = itemTemplate.material[mRNG.RandomNumber(0, itemTemplate.material.size() - 1)];
	std::string piece = itemTemplate.piece[mRNG.RandomNumber(0, itemTemplate.piece.size() - 1)];
	std::string name = material + " " + piece;

	EquipmentSlot slot = itemTemplate.slot;

	ItemQuality quality = RollQuality();

	int stats[4] = { 0, 0, 0, 0 };
	std::vector<int> possibleStats;

	if (itemTemplate.strength)
		possibleStats.push_back(0);
	if (itemTemplate.agility)
		possibleStats.push_back(1);
	if (itemTemplate.intellect)
		possibleStats.push_back(2);
	if (itemTemplate.spirit)
		possibleStats.push_back(3);

	int statPos = mRNG.RandomNumber(0, possibleStats.size() - 1);
	int statIndex = possibleStats[statPos];
	stats[statIndex] = RollStat(tier, quality);

	if (possibleStats.size() > 1 && mRNG.RandomNumber(0, 1) == 0)
	{
		stats[statIndex] = ceil((float)stats[statIndex] * 0.66f);
		possibleStats.erase(possibleStats.begin() + statPos);

		statIndex = possibleStats[mRNG.RandomNumber(0, possibleStats.size() - 1)];
		stats[statIndex] = ceil((float)RollStat(tier, quality) * 0.66f);
	}

	int stamina = 0;
	if (mRNG.RandomNumber(0, 1) == 0)
		stamina = RollStat(tier, quality);

	int defense = RollArmorValue(tier) * itemTemplate.defenseModifier;
	int resistance = RollArmorValue(tier) * itemTemplate.defenseModifier;

	Armor* armor = new Armor(name, Sprite(0, 0, { 255, 255, 255 }), slot, quality, tier,
		stats[0], stats[1], stats[2], stats[3], stamina, defense, resistance);

	return armor;
}

Equippable * ItemBuilder::GetRandomEquippable(int tier)
{
	return nullptr;
}
