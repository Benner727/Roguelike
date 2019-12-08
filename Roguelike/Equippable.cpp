#include "Equippable.h"



Equippable::Equippable(std::string name, Sprite sprite, EquipmentSlot slot, ItemQuality quality, int tier, int strength, int agility, int intellect, int spirit, int stamina)
	: Item(name, sprite), mSlot(slot), mQuality(quality), mTier(tier), mStrength(strength), mAgility(agility), mIntellect(mIntellect), mSpirit(spirit), mStamina(stamina)
{

}


Equippable::~Equippable()
{
}
