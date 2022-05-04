#include "spider.h"

/*
2.	One of them should call the constructor of the base class explicitly,
and the other to be “using” the base class constructor.*/

spider::spider(std::string name_, int climbHeight)
	: enemy (name_, climbHeight)
{

}
