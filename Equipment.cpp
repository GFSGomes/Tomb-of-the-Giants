#include "Equipment.hpp"

Equipment::Equipment(const char* _name) : Item(_name, 1)
{

}

Equipment::~Equipment()
{

}

short Equipment::Use()
{
	return 0;
}

void Equipment::Equip()
{

}