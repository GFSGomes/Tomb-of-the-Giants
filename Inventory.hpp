#pragma once
#define NOMINMAX
#include "Slot.hpp"
#include "Equipment.hpp"
#include "Renderer.hpp"
#include <vector>
#include <conio.h>
#include <limits>
#include <memory>
#include <conio.h>

struct Inventory
{
	bool active;
	short index;
	char input;
	bool organize;
	std::vector<Slot> Container;
	std::shared_ptr<Slot> hoveredSlot;
	std::shared_ptr<Slot> selectedSlot;

	Inventory();

	~Inventory();

	std::shared_ptr<Slot> GetSlot(std::shared_ptr<Item>);

	int GetSlotIndex(std::shared_ptr<Slot>);

	void AddItem(std::shared_ptr<Item>, short);

	void DiscardItem(std::shared_ptr<Item>, short, bool);

	void OrganizeSlots();

	std::shared_ptr<Item> Initialize();
};