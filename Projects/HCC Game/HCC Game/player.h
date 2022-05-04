#pragma once
#include <string>
#include "Model.h"
class player : public Model {
public:
	std::string pName;
	int skillLevel;
	int stamina;
	player();

	int getHealth();
	void displayStats();
	void setName(std::string name);
	void healPlayer(int healAmount);
};

