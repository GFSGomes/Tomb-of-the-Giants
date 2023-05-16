#include "Slot.hpp"
#include "Item.hpp"

Slot::Slot(std::shared_ptr<Item> _item, short _amount) : item{_item}, amount{_amount}
{

}

Slot::~Slot()
{

}