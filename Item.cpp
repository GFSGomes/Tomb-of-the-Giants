#include "Item.hpp"

Item::Item(const char* _name, short _stack = 1) : stack{_stack}
{
	strcpy_s(name, _name);
}

Item::~Item()
{

}

short Item::Use()
{
	return 0;
}