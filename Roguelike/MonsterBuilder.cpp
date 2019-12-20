#include "MonsterBuilder.h"



std::vector<MonsterBuilder::MonsterTemplate> MonsterBuilder::mMonsterTemplates =
{
	MonsterTemplate(Sprite(25, 2, {128, 156, 0}), "Goblin", 5, 5, 25, CombatType::melee, 1, 5, 5),
	MonsterTemplate(Sprite(26, 2, {0, 128, 56}), "Orc", 10, 10, 45, CombatType::melee, 1, 15, 15),
	MonsterTemplate(Sprite(29, 6, {200, 200, 200}), "Skeleton", 7, 7, 35, CombatType::ranged, 4, 10, 10),
	MonsterTemplate(Sprite(29, 2, {128, 0, 0}), "Demon", 5, 5, 35, CombatType::magic, 4, 30, 30),
	MonsterTemplate(Sprite(26, 6, {155, 235, 250}), "Ghost", 15, 15, 50, CombatType::magic, 6, 10, 10)
};

MonsterBuilder::MonsterBuilder()
	: mRNG(RNG(time(nullptr)))
{
}


MonsterBuilder::~MonsterBuilder()
{
}

Monster * MonsterBuilder::GetNormalMonster(int tier, Point pos)
{
	MonsterTemplate monsterTemplate = mMonsterTemplates[mRNG.RandomNumber(0, mMonsterTemplates.size() - 1)];

	std::string name = monsterTemplate.name;

	int strength = 0;
	int agility = 0;
	int intellect = 0;
	int spirit = 0;

	switch (monsterTemplate.type)
	{
	case CombatType::melee:
		strength = monsterTemplate.primaryStat * tier;
		break;
	case CombatType::ranged:
		agility = monsterTemplate.primaryStat * tier;
		break;
	case CombatType::magic:
		intellect = monsterTemplate.primaryStat * tier;
		break;
	}

	int stamina = monsterTemplate.stamina * tier;

	int damage = (1.0f + ((float)tier / 10.0f) * 2.0f) * monsterTemplate.damage * 2.5f;

	int defense = (1.0f + ((float)tier / 5.0f) * 2.0f) * monsterTemplate.defense * 1.7f;
	int resistance = (1.0f + ((float)tier / 5.0f) * 2.0f) * monsterTemplate.resistance * 1.7f;

	Monster* monster = new Monster(pos, monsterTemplate.sprite, name, false, 
		strength, agility, intellect, spirit, stamina, damage, monsterTemplate.type, 
		monsterTemplate.range, defense, resistance);

	return monster;
}

Monster * MonsterBuilder::GetEliteMonster(int tier, Point pos)
{
	MonsterTemplate monsterTemplate = mMonsterTemplates[mRNG.RandomNumber(0, mMonsterTemplates.size() - 1)];

	std::string name = monsterTemplate.name;

	int strength = 0;
	int agility = 0;
	int intellect = 0;
	int spirit = 0;

	switch (monsterTemplate.type)
	{
	case CombatType::melee:
		strength = monsterTemplate.primaryStat * tier * 2.0f;
		break;
	case CombatType::ranged:
		agility = monsterTemplate.primaryStat * tier * 2.0f;
		break;
	case CombatType::magic:
		intellect = monsterTemplate.primaryStat * tier * 2.0f;
		break;
	}

	int stamina = monsterTemplate.stamina * tier * 2.5f;

	int damage = (1.0f + ((float)tier / 10.0f) * 2.0f) * monsterTemplate.damage * 3.5f;

	int defense = (1.0f + ((float)tier / 5.0f) * 2.0f) * monsterTemplate.defense * 3.4f;
	int resistance = (1.0f + ((float)tier / 5.0f) * 2.0f) * monsterTemplate.resistance * 3.4f;

	Monster* monster = new Monster(pos, monsterTemplate.sprite, name, true,
		strength, agility, intellect, spirit, stamina, damage, monsterTemplate.type,
		monsterTemplate.range, defense, resistance);

	return monster;
}

Monster * MonsterBuilder::GetRandomMonster(int tier, Point pos)
{
	if (mRNG.RandomNumber(0, 99) < ELITE_CHANCE)
		return GetEliteMonster(tier, pos);
	else
		return GetRandomMonster(tier, pos);
}
