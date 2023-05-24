#pragma once
#define NOMINMAX
#include <vector>
#include <memory>
#include "Slot.hpp" // Importante pois vector precisa saber o tamanho em bytes do Objeto;

struct Item;

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

	void AddItem(std::shared_ptr<Item>, short _amount = 1);

	short DiscardItem(std::shared_ptr<Item>, short _amount = 0, bool _itemBeingUse = false);

	void OrganizeSlots();

	std::shared_ptr<Item> Initialize();
};