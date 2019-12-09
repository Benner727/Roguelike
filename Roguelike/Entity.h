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
	static const int SPRITE_TILE_X = 25;
	static const int SPRITE_TILE_Y = 0;
	static const int MAX_HEALTH = 100;

	std::string name;
	int health = MAX_HEALTH;
	Sprite mSprite;
	
	int xPosition;
	int yPosition;
	void Move(int x, int y);



public:
	const std::string GetName() { return name; }
	const int GetHealth() { return health; }
	const int GetXPos() { return xPosition; }
	const int GetYPos() { return yPosition; }

	void setName(std::string newName) { name = newName;  }
	void changeHealth(int healthDiff) { health += healthDiff; }
	void Move(Point pos);
	void Draw();
};

#endif