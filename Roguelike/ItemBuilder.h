#ifndef ITEMBUILDER_H
#define ITEMBUILDER_H

#include <map>

#include "Weapon.h"
#include "Armor.h"
#include "RNG.h"

class ItemBuilder
{
public:
	ItemBuilder();
	~ItemBuilder();

private:
	struct WeaponTemplate {
		EquipmentSlot slot;
		std::vector<std::string> material;
		std::vector<std::string> piece;
		CombatType type;
		float damageModifier;
		int range;
		bool twoHanded;
		bool strength;
		bool agility;
		bool intellect;
		bool spirit;

		WeaponTemplate(std::vector<std::string> _material, std::vector<std::string> _piece,
			CombatType _type, float _damageModifier, int _range, bool _twoHanded, 
			bool _strength, bool _agility, bool _intellect, bool _spirit)
			: material(_material), piece(_piece), type(_type), 
			damageModifier(_damageModifier), range(_range), twoHanded(_twoHanded), 
			strength(_strength), agility(_agility), intellect(_intellect), spirit(_spirit)
		{
			slot = EquipmentSlot::weapon;
		}
	};

	struct ArmorTemplate {
		EquipmentSlot slot;
		std::vector<std::string> material;
		std::vector<std::string> piece;
		float defenseModifier;
		bool strength;
		bool agility;
		bool intellect;
		bool spirit;

		ArmorTemplate(EquipmentSlot _slot, std::vector<std::string> _material, std::vector<std::string> _piece,
			float _defenseModifier, bool _strength, bool _agility, bool _intellect, bool _spirit)
			: slot(_slot), material(_material), piece(_piece), defenseModifier(_defenseModifier),
			strength(_strength), agility(_agility), intellect(_intellect), spirit(_spirit)
		{}
	};

	static std::vector<WeaponTemplate> mWeaponTemplates;
	static std::vector<ArmorTemplate> mArmorTemplates;

	RNG mRNG;

	ItemQuality RollQuality();
	EquipmentSlot RollSlot(bool includeWeapon);
	int RollStat(int tier, ItemQuality quality);
	int RollDamage(int tier);
	int RollArmorValue(int tier);

public:
	Weapon* GetRandomWeapon(int tier);
	Armor* GetRandomArmor(int tier);
	Equippable* GetRandomEquippable(int tier);
};

#endif