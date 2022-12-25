#include "Menu.hpp"
#include "Slot.hpp"
#include <vector>
#include <conio.h>

struct Inventory : Menu
{
	bool remove;
	bool organize;
	std::vector<Slot> Container;
	std::shared_ptr<Slot> hoveredSlot;
	std::shared_ptr<Slot> selectedSlot;

	Inventory();

	~Inventory();

	void AddItem(std::shared_ptr<Item>, short);
	void DiscardItem(std::shared_ptr<Item>);
	int GetSlotIndex(std::shared_ptr<Slot>);
	void OrganizeSlots();
	void Initialize();
};