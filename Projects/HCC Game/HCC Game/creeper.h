#pragma once
#include "enemy.h"
class creeper : public enemy
{
	/*3.	Make at least one data member of your enemy class protected rather than private.
Access this member appropriately from one of the new enemy classes.*/
public:
	creeper();
	int getID();
};

