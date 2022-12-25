#include "Potion.hpp"

Potion::Potion(const char* _name) : Item(_name, 3) //Stack
{
	name = _name;
}

Potion::~Potion()
{

}

void Potion::Use()
{

}