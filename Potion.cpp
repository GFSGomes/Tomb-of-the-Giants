#include "Potion.hpp"
#include "Player.hpp"

Potion::Potion(const char* _name) : Item(_name, 5) //Stack
{
	strcpy_s(name, _name);
}

Potion::~Potion()
{

}

void Potion::Use()
{
	
}