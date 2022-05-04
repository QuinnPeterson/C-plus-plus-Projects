#include "player.h"

#include <string>
#include <conio.h>
#include <iostream>

player::player()
{
	health = 10;
	skillLevel = 1;
	stamina = 8;
}

void player::setName(std::string name)
{
	this->pName = name;
}

void player::healPlayer(int healAmount)
{
	this->health = healAmount;
	this->stamina = 8;
}

void player::displayStats()
{
	std::cout << "--------STATS--------\n"
		<< "Player name: " << pName << std::endl
		<< "--------------------------" << std::endl
		<< "Health: " << health << std::endl
		<< "Stamina: " << stamina << std::endl
		<< "Skill Level: " << skillLevel << std::endl
		<< std::endl << "Press enter to go back to menu.\n";
	_getch();
}

int player::getHealth()
{
	return this->health;
}
