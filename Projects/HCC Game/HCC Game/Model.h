#pragma once
#include <string>
class Model
{
public:
	int health;
	bool isDead;
	std::string name;
	bool hasDied();
	int id;

	void doAttack(Model& target, int damage);

	int getID();
	void setID(int newId);
};

