#include "Model.h"


bool Model::hasDied()
{
	if (health <= 0)
		return true;
	else
		return false;
}

void Model::doAttack(Model& target, int damage)
{
	target.health -= damage;
}

int Model::getID()
{
	return this->id;
}

void Model::setID(int newId)
{
	this->id = newId;
}
