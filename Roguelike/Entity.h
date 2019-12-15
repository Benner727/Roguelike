#ifndef ENTITY_H
#define ENTITY_H

#include "MathHelper.h"
#include "Sprite.h"

class Entity
{
public:
	Entity(int x = 0, int y = 0, int spriteX = SPRITE_TILE_X, int spriteY = SPRITE_TILE_Y);
	Entity(Point pos);
	~Entity();

protected:
	Sprite mSprite;
	static const int SPRITE_TILE_X = 25;
	static const int SPRITE_TILE_Y = 0;
	
	std::string name;
	int health;
	int strength;
	int intellect;
	int spirit;
	int stamina;
	int armor;
	int resistance;
	
	int xPosition;
	int yPosition;
	void Move(int x, int y);


public:
	const std::string GetName() { return name; }
	const int GetHealth() { return health; }
	const int GetStrength() { return strength; }
	const int GetIntellect() { return intellect; }
	const int GetSpirit() { return spirit; }
	const int GetStamina() { return stamina; }
	const int GetArmor() { return armor; }
	const int GetResistance() { return resistance; }

	bool Dead() { return health <= 0;  }
	void Heal(int amount) { health += amount; }
	void TakeDamage(int amount) { health -= amount; }

	const int GetXPos() { return xPosition; }
	const int GetYPos() { return yPosition; }
	void Move(Point pos);
	void Draw();
};

#endif