
static int numberOfEnemies = 0;

#pragma once
#include <string>
#include "Model.h"

class enemy : public Model {
public:
	enemy(std::string type, int playerLevel);
	enemy();
	~enemy();
	std::string name;
	int health;
	
	
/*3.	Make at least one data member of your enemy class protected rather than private. 
Access this member appropriately from one of the new enemy classes.*/
protected: 
	int id;

};

