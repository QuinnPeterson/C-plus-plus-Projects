#include "creeper.h"

creeper::creeper()
{
	this->name = "creeper";
	this->health = 9;

	getID();
}

/*3.	Make at least one data member of your enemy class protected rather than private.
Access this member appropriately from one of the new enemy classes.*/
int creeper::getID()
{
	return id;
}
