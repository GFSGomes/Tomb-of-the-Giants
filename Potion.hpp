#include "Item.hpp"

struct Potion : Item
{
	Potion(const char*);
	~Potion();

	short Use();
};