#ifndef ITEMBUILDER_H
#define ITEMBUILDER_H

#include "Weapon.h"
#include "Armor.h"
#include "RNG.h"

class ItemBuilder
{
public:
	ItemBuilder();
	~ItemBuilder();

private:
	enum Stat { Strength, Agility, Intellect, Spirit, TOTAL_STATS };

	struct WeaponTemplate {
		EquipmentSlot slot;
		std::vector<std::string> material;
		std::vector<std::string> piece;
		CombatType type;
		float damageModifier;
		int range;
		bool twoHanded;
		std::vector<Stat> primary;
		std::vector<Stat> secondary;

		WeaponTemplate(std::vector<std::string> _material, std::vector<std::string> _piece,
			CombatType _type, float _damageModifier, int _range, bool _twoHanded, 
			std::vector<Stat> _primary, std::vector<Stat> _secondary)
			: material(_material), piece(_piece), type(_type), 
			damageModifier(_damageModifier), range(_range), twoHanded(_twoHanded), 
			primary(_primary), secondary(_secondary)
		{
			slot = EquipmentSlot::weapon;
		}
	};

	struct ArmorTemplate {
		EquipmentSlot slot;
		std::vector<std::string> material;
		std::vector<std::string> piece;
		float defenseModifier;
		std::vector<Stat> primary;
		std::vector<Stat> secondary;

		ArmorTemplate(EquipmentSlot _slot, std::vector<std::string> _material, std::vector<std::string> _piece,
			float _defenseModifier, std::vector<Stat> _primary, std::vector<Stat> _secondary)
			: slot(_slot), material(_material), piece(_piece), defenseModifier(_defenseModifier),
			primary(_primary), secondary(_secondary)
		{}
	};

	static std::vector<WeaponTemplate> mWeaponTemplates;
	static std::vector<ArmorTemplate> mArmorTemplates;

	RNG mRNG;

	ItemQuality RollQuality();
	int RollStat(int tier, ItemQuality quality);
	int RollDamage(int tier);
	int RollArmorValue(int tier);
	SDL_Color ItemColor(ItemQuality quality);

public:
	Weapon* GetRandomWeapon(int tier);
	Armor* GetRandomArmor(int tier);
	Equippable* GetRandomEquippable(int tier);
};

#endif