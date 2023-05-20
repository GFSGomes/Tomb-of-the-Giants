#include "Consumable.hpp"

Consumable::Consumable(const char * _name, short _maxStack) : Item{_name, _maxStack}
{

}

Consumable::~Consumable()
{

}

float Consumable::Use(std::shared_ptr<Entity>)
{
	return 0;
}