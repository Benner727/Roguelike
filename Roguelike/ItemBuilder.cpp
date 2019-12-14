#include "ItemBuilder.h"



std::vector<ItemBuilder::WeaponTemplate> ItemBuilder::mWeaponTemplates =
{
	//Melee
	WeaponTemplate({"Bronze", "Iron", "Steel"}, {"Sword"}, CombatType::melee, 2.5f, 1, false, {Stat::Strength}, {}),
	WeaponTemplate({"Bronze", "Iron", "Steel"}, {"Mace"}, CombatType::melee, 2.5f, 1, false, {Stat::Strength}, {Stat::Spirit}),
	WeaponTemplate({"Bronze", "Iron", "Steel"}, {"Greataxe"}, CombatType::melee, 3.5f, 1, true, {Stat::Strength}, {}),
	WeaponTemplate({"Bronze", "Iron", "Steel"}, {"Maul"}, CombatType::melee, 3.5f, 1, true, {Stat::Strength}, {Stat::Spirit}),

	//Ranged
	WeaponTemplate({"Wood"}, {"Recurve Bow"}, CombatType::ranged, 3.5f, 6, true, {Stat::Agility}, {}),
	WeaponTemplate({"Wood"}, {"Long Bow"}, CombatType::ranged, 3.0f, 8, true, {Stat::Agility}, {}),
	WeaponTemplate({"Wood"}, {"Crossbow"}, CombatType::ranged, 2.5f, 4, false, {Stat::Agility}, {Stat::Spirit}),

	//Magic
	WeaponTemplate({"Wood"}, {"Staff"}, CombatType::magic, 3.5f, 7, true, {Stat::Intellect}, {Stat::Spirit}),
	WeaponTemplate({"Wood"}, {"Wand"}, CombatType::magic, 2.5f, 5, false, {Stat::Intellect}, {Stat::Spirit}),
};

std::vector<ItemBuilder::ArmorTemplate> ItemBuilder::mArmorTemplates =
{
	//Melee
	ArmorTemplate(EquipmentSlot::head, {"Bronze", "Iron", "Steel"}, {"Faceguard", "Helmet"}, 0.35f, {Stat::Strength}, {Stat::Spirit}),
	ArmorTemplate(EquipmentSlot::chest, {"Bronze", "Iron", "Steel"}, {"Hauberk", "Platebody"}, 1.0f, {Stat::Strength}, {Stat::Spirit}),
	ArmorTemplate(EquipmentSlot::legs, {"Bronze", "Iron", "Steel"}, {"Tassets", "Platelegs"}, 0.85f, {Stat::Strength}, {Stat::Spirit}),
	ArmorTemplate(EquipmentSlot::gloves, {"Bronze", "Iron", "Steel"}, {"Gauntlets", "Gloves"}, 0.25f, {Stat::Strength}, {Stat::Spirit}),
	ArmorTemplate(EquipmentSlot::boots, {"Bronze", "Iron", "Steel"}, {"Greaves", "Boots"}, 0.25f, {Stat::Strength}, {Stat::Spirit}),

	//Ranged
	ArmorTemplate(EquipmentSlot::head, {"Leather", "Hide", "Chain"}, {"Cowl", "Coif"}, 0.25f, {Stat::Agility}, {Stat::Spirit}),
	ArmorTemplate(EquipmentSlot::chest, {"Leather", "Hide", "Chain"}, {"Tunic", "Body"}, 0.9f, {Stat::Agility}, {Stat::Spirit}),
	ArmorTemplate(EquipmentSlot::legs, {"Leather", "Hide", "Chain"}, {"Chaps", "Pants"}, 0.75f, {Stat::Agility}, {Stat::Spirit}),
	ArmorTemplate(EquipmentSlot::gloves, {"Leather", "Hide", "Chain"}, {"Vambraces", "Gloves"}, 0.15f, {Stat::Agility}, {Stat::Spirit}),
	ArmorTemplate(EquipmentSlot::boots, {"Leather", "Hide", "Chain"}, {"Shoes", "Boots"}, 0.15f, {Stat::Agility}, {Stat::Spirit}),

	//Magic
	ArmorTemplate(EquipmentSlot::head, {"Cloth", "Silk"}, {"Hood", "Hat"}, 0.20f, {Stat::Intellect}, {Stat::Spirit}),
	ArmorTemplate(EquipmentSlot::chest, {"Cloth", "Silk"}, {"Robe", "Shirt"}, 0.85f, {Stat::Intellect}, {Stat::Spirit}),
	ArmorTemplate(EquipmentSlot::legs, {"Cloth", "Silk"}, {"Skirt", "Leggings"}, 0.70f, {Stat::Intellect}, {Stat::Spirit}),
	ArmorTemplate(EquipmentSlot::gloves, {"Cloth", "Silk"}, {"Wraps", "Gloves"}, 0.10f, {Stat::Intellect}, {Stat::Spirit}),
	ArmorTemplate(EquipmentSlot::boots, {"Cloth", "Silk"}, {"Socks", "Slippers"}, 0.10f, {Stat::Intellect}, {Stat::Spirit}),

	//Offhand
	ArmorTemplate(EquipmentSlot::shield, {"Wood"}, {"Buckler"}, 0.35f, {Stat::Strength, Stat::Agility}, {Stat::Spirit}),
	ArmorTemplate(EquipmentSlot::shield, {"Bronze", "Iron", "Steel" }, {"Shield"}, 0.50f, {Stat::Strength}, {Stat::Spirit}),
	ArmorTemplate(EquipmentSlot::shield, {"Green", "Pink"}, {"Ward"}, 0.10f, {Stat::Intellect}, {Stat::Spirit}),
	ArmorTemplate(EquipmentSlot::shield, {"Flame", "Earth", "Wind"}, {"Totem"}, 0.05f, {Stat::Spirit}, {Stat::Intellect}),

	//Misc
	ArmorTemplate(EquipmentSlot::cloak, {"Fur", "Scale"}, {"Cape", "Cloak"}, 0.10f, {Stat::Strength, Stat::Agility, Stat::Agility}, {Stat::Spirit}),
	ArmorTemplate(EquipmentSlot::amulet, {"Brass", "Silver", "Gold"}, {"Amulet", "Necklace"}, 0.0f, {Stat::Strength, Stat::Agility, Stat::Agility}, {Stat::Spirit}),
	ArmorTemplate(EquipmentSlot::ring, {"Brass", "Silver", "Gold"}, {"Ring", "Heirloom"}, 0.0f, {Stat::Strength, Stat::Agility, Stat::Agility}, {Stat::Spirit})
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

	std::vector<int> stats(Stat::TOTAL_STATS, 0);

	Stat primaryStat = itemTemplate.primary[mRNG.RandomNumber(0, itemTemplate.primary.size() - 1)];
	stats[primaryStat] = RollStat(tier, quality);

	if (itemTemplate.secondary.size() > 0 && mRNG.RandomNumber(0, 1) == 0)
	{
		stats[primaryStat] = ceil((float)stats[primaryStat] * 0.66f);

		Stat secondaryStat = itemTemplate.secondary[mRNG.RandomNumber(0, itemTemplate.secondary.size() - 1)];
		stats[secondaryStat] = ceil(RollStat(tier, quality) * 0.66f);
	}

	int stamina = 0;

	int damage = RollDamage(tier) * itemTemplate.damageModifier;

	Weapon* weapon = new Weapon(name, Sprite(0, 0, { 255, 255, 255 }), quality, tier,
		stats[Stat::Strength], stats[Stat::Agility], stats[Stat::Intellect], stats[Stat::Spirit], stamina, damage,
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

	std::vector<int> stats(Stat::TOTAL_STATS, 0);

	Stat primaryStat = itemTemplate.primary[mRNG.RandomNumber(0, itemTemplate.primary.size() - 1)];
	stats[primaryStat] = RollStat(tier, quality);

	if (itemTemplate.secondary.size() > 0 && mRNG.RandomNumber(0, 1) == 0)
	{
		stats[primaryStat] = ceil((float)stats[primaryStat] * 0.66f);

		Stat secondaryStat = itemTemplate.secondary[mRNG.RandomNumber(0, itemTemplate.secondary.size() - 1)];
		stats[secondaryStat] = ceil(RollStat(tier, quality) * 0.66f);
	}

	int stamina = 0;
	if (mRNG.RandomNumber(0, 1) == 0)
		stamina = RollStat(tier, quality);

	int defense = RollArmorValue(tier) * itemTemplate.defenseModifier;
	int resistance = RollArmorValue(tier) * itemTemplate.defenseModifier;

	if (mRNG.RandomNumber(0, 1) == 0)
		ceil(defense *= 0.66f);
	else
		ceil(resistance *= 0.66f);

	Armor* armor = new Armor(name, Sprite(0, 0, { 255, 255, 255 }), slot, quality, tier,
		stats[Stat::Strength], stats[Stat::Agility], stats[Stat::Intellect], stats[Stat::Spirit], 
		stamina, defense, resistance);

	return armor;
}

Equippable * ItemBuilder::GetRandomEquippable(int tier)
{
	return nullptr;
}
