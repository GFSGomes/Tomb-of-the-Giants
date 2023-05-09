#include "Item.hpp";

Item::Item(const char* _name = "New Item", short _stack = 1) : stack{_stack}
{
	name = _name;
	active = true;
}

Item::~Item()
{

}