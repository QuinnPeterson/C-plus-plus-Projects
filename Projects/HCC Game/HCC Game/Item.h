#pragma once
#include <string>
struct Item
{
public:
	std::string name;
	int useVal;
	int durability;
	int id = 0;
	int damage;

	Item()
	{
		useVal = -1;
	}

	Item(std::string name_, int useVal_) {
		this->name = name_;
		this->useVal = useVal_;
	}

	std::string getName() {
		return name;
	}
	void setName(std::string newName) {
		name = newName;
	}



};