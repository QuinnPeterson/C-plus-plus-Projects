#pragma once
#include "attack.h"
#include "Item.h"
#include <string>
class weapon : public Item
{
public:
	int staminaCost;
	attack curAttack;
	weapon();
	weapon(std::string name_, int durability_, int attackAtMinimum_, int staminaCost_);
};

