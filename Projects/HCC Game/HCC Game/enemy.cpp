#include "enemy.h"
#include <iostream>



enemy::enemy(std::string type, int playerLevel)
{
	this->health = 10;
	this->name = type;
	playerLevel = 1;
	id++;
}

enemy::enemy()
{
	this->health = 10;
	this->name = "zombie";
	id++;

}

enemy::~enemy()
{
	numberOfEnemies--;
}

