#ifndef ENTITY_H
#define ENTITY_H

#include "MathHelper.h"
#include "Sprite.h"

class Entity
{
public:
	Entity(Point pos, Sprite sprite);
	~Entity();

protected:
	Sprite mSprite;
	
	std::string mName;
	Point mPos;

	int mHealth;
	int mMaxHealth;

	int mStrength;
	int mIntellect;
	int mSpirit;
	int mStamina;
	int mDefense;
	int mResistance;

	void Move(int x, int y);

public:
	std::string Name() const { return mName; }
	void Rename(std::string name) { mName = name; }

	int Health() const { return mHealth; }
	int MaxHealth() const { return mMaxHealth; }

	int Strength() const { return mStrength; }
	int Intellect() const { return mIntellect; }
	int Spirit() const { return mSpirit; }
	int Stamina() const { return mStamina; }
	int Defense() const { return mDefense; }
	int Resistance() const { return mResistance; }

	bool Dead() { return mHealth < 1;  }
	void Heal(int amount) { mHealth += amount; if (mHealth > mMaxHealth) mHealth = mMaxHealth; }
	void TakeDamage(int amount) { mHealth -= amount; }

	int GetXPos() const { return mPos.tileX; }
	int GetYPos() const { return mPos.tileY; }
	Point Position() const { return mPos; }
	void Move(Point pos);

	void Draw();
};

#endif