#include "Monster.h"



Monster::Monster(Point pos, Sprite sprite, std::string name, bool elite,
	int strength, int agility, int intellect, int spirit, int stamina,
	int damage, CombatType type, int range,
	int defense, int resistance)
	: Entity(pos, sprite), mElite(elite)
{
	mName = name;

	mStrength = strength;
	mAgility = agility;
	mIntellect = intellect;
	mSpirit = spirit;
	mStamina = stamina;

	mDamage = damage;
	mDamageType = type;
	mAttackRange = range;

	mDefense = defense;
	mResistance = resistance;

	mMaxHealth = ((float)mStamina / 4.0f) * 100 + 100;
	mHealth = mMaxHealth;
}


Monster::~Monster()
{
}
