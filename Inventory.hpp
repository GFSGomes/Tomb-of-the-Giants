#pragma once
#include "GUI.hpp"
#include "Slot.hpp"
#include <vector>
#include <conio.h>
#include "Equipment.hpp" //

struct Inventory : GUI
{
	bool remove;
	bool organize;
	std::vector<Slot> Container;
	std::shared_ptr<Slot> hoveredSlot;
	std::shared_ptr<Slot> selectedSlot;

	Inventory();

	~Inventory();

	std::shared_ptr<Slot> GetSlot(std::shared_ptr<Item>);

	int GetSlotIndex(std::shared_ptr<Slot>);

	void AddItem(std::shared_ptr<Item>, short);

	void DiscardItem(std::shared_ptr<Item>);

	void OrganizeSlots();

	std::shared_ptr<Item> Initialize();
};