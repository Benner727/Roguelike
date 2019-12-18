#ifndef MONSTER_H
#define MONSTER_H

#include "Entity.h"

class Monster : public Entity
{
public:
	Monster(Point pos, Sprite sprite, std::string name,
		int strength, int agility, int intellect, int spirit, int stamina,
		int damage, CombatType type, int range,
		int defense, int resistance);

	~Monster();
};

#endif