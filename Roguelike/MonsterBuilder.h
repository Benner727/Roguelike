#ifndef MONSTERBUILDER_H
#define MONSTERBUILDER_H

#include "Monster.h"
#include "RNG.h"

class MonsterBuilder
{
public:
	MonsterBuilder();
	~MonsterBuilder();

private:
	static const int ELITE_CHANCE = 5; // Percentage to spawn

	struct MonsterTemplate {

		Sprite sprite;
		std::string name;
		int primaryStat;
		int stamina;
		int damage;
		CombatType type;
		int range;
		int defense;
		int resistance;

		MonsterTemplate(Sprite _sprite, std::string _name, 
			int _primaryStat, int _stamina, int _damage, CombatType _type,
			int _range, int _defense, int _resistance)
			: sprite(_sprite), name(_name), primaryStat(_primaryStat), stamina(_stamina),
			damage(_damage), type(_type), range(_range), defense(_defense), resistance(_resistance)
		{ }
	};

	static std::vector<MonsterTemplate> mMonsterTemplates;

	RNG mRNG;

public:
	Monster* GetNormalMonster(int tier, Point pos);
	Monster* GetEliteMonster(int tier, Point pos);
	Monster* GetRandomMonster(int tier, Point pos);

};

#endif