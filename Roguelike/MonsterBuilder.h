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
	RNG mRNG;
};

#endif