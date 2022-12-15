#include "Item.hpp"

struct Slot
{
	Item* item;
	short amount;

	Slot(Item*, short);

	~Slot();
};