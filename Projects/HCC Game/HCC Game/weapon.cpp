#include "weapon.h"


weapon::weapon()
{

}

weapon::weapon(std::string name_, int durability_, int attackAtMinimum_, int staminaCost_)
{
	setName(name_);
	useVal = 0;


	this->damage = attackAtMinimum_;
	this->durability = durability_;
	this->staminaCost = staminaCost_;

	this->curAttack.attackPower = damage;
	this->curAttack.staminaCost = staminaCost;

}

