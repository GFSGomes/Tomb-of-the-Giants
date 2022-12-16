#include "Menu.hpp"
#include "Slot.hpp"
#include <vector>
#include <conio.h>

struct Inventory : Menu
{
	bool remove;
	bool organize;
	Slot* hoveredSlot;
	Slot* selectedSlot;
	std::vector<Slot> Container;

	Inventory();

	~Inventory();

	void AddItem(Item*, short);
	void DiscardItem(Item*);
	int GetItemIndex(Slot*);
	void OrganizeSlots();
	void Initialize();
};