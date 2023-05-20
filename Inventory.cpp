#include "Inventory.hpp"
#include "Renderer.hpp"
#include "Item.hpp"
#include "Slot.hpp"
#include "Equipment.hpp"//
#include <conio.h>

Inventory::Inventory() : active{false}, index{0}, input{'\0'}, Container{}, hoveredSlot{nullptr}, selectedSlot{nullptr}, organize{false}
{

}

Inventory::~Inventory()
{

}

void Inventory::AddItem(std::shared_ptr<Item> _item, short _amount)
{
	while (_amount > _item->stack)
	{
		Container.push_back(Slot(_item, _item->stack));
		_amount -= _item->stack;
	}

	if (_amount > 0)
	{
		if (Container.empty())
		{
			Container.push_back(Slot(_item, _amount));
		}
		else
		{
			for (short i = 0; i < Container.size(); i++)
			{
				// Se o Item já está no Inventário:
				if (Container[i].item->name == _item->name)
				{
					// Procurando um Slot não-cheio:
					for (short j = 0; j < Container.size(); j++)
					{
						if (Container[j].amount <= Container[j].item->stack)
						{
							Container[j].amount += _amount;

							// Caso ultrapassar:
							if (Container[j].amount > Container[j].item->stack)
							{
								short over = Container[j].amount - Container[j].item->stack;
								Container[j].amount -= over;

								if (over > 0)
									Container.push_back(Slot(_item, over));
							}
							return;
						}
					}

					short over = (Container[i].amount + _amount) - Container[i].item->stack;

					Container[i].amount += (_amount - over);

					Container.push_back(Slot(_item, over));
					return;
				}

				else
				{
					for (short j = 0; j < Container.size(); j++)
					{
						if (Container[j].item->name == _item->name)
						{
							if (Container[j].amount < Container[j].item->stack)
							{
								Container[j].amount += _amount;

								if (Container[j].amount >= Container[j].item->stack)
								{
									short over = Container[j].amount - Container[j].item->stack;

									Container[j].amount -= over;

									if (over > 0)
									{
										Container.push_back(Slot(_item, over));
									}
								}
								return;
							}
						}
					}

					// Se o Item não está no Inventário:
					Container.push_back(Slot(_item, _amount));
					return;
				}
			}
		}
	}
}

int Inventory::GetSlotIndex(std::shared_ptr<Slot> _slot)
{
	for (int i = 0; i < Container.size(); i++)
	{
		if (std::make_shared<Slot>(Container[i])->item == _slot->item)
		{
			return i;
		}
	}

	return NULL;
}

std::shared_ptr<Slot> Inventory::GetSlot(std::shared_ptr<Item> _item)
{
	for (int i = 0; i < Container.size(); i++)
	{
		if (std::make_shared<Slot>(Container[i])->item == _item)
		{
			std::shared_ptr<Slot> slot = std::make_shared<Slot>(Container[i]);
			return slot;
		}
	}

	return nullptr;
}

void Inventory::DiscardItem(std::shared_ptr<Item> _item, short _amount, bool _usingItem)
{
	active = true;

	if (_amount == 0)
	{
		std::cout << "\n";
		std::cout << " | [?] How many " << _item->name << " do you'd like to discard?" << "\n";
		std::cout << " | > ";
	}

	short _index = 0;
	bool _active = true;
	char _input = '\0';

	short amount = _amount;

	while (active)
	{
		if (_amount == 0)
		{
			std::cin >> amount;
			if (amount == 0)
			{
				active = false;
				return;
			}

			if (!std::cin)
			{
				std::cout << " | [!] Please, enter a integer:" << std::endl;
				std::cin.clear();
				std::cout << " | > ";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
		}

		// Confirmação
		while (_active && !_usingItem)
		{
			system("cls");
			std::cout << "\n";
			std::cout << " | [!] " << _item->name << " will be discarded:" << "\n";
			Renderer::DisplaySprite(_item->sprite);
			std::cout << "\n";
			std::cout << " | Are you sure?" << "\n";
			std::cout << " | " << "\n";

			switch (_index)
			{
				case 0:
				{
					std::cout << " | > Yes" << "\n";
					std::cout << " |   No" << "\n";
					break;
				}
				case 1:
				{
					std::cout << " |   Yes" << "\n";
					std::cout << " | > No" << "\n";
					break;
				}
			}

			_input = _getch();

			switch (_input)
			{
				case 'w': case 'W':
				{
					if (_index > 0) _index--;
					break;
				}
				case 's': case 'S':
				{
					if (_index < 1) _index++;
					break;
				}
				case '\r':
				{
					switch (_index)
					{
						case 0:
						{
							_active = false;
							continue;
						}
						case 1:
						{
							active = false;
							_active = false;
							return;
						}
					}
				}
				case 27:
				{
					active = false;
					_active = false;
					return;
				}
			}
		}

		if (!Container.empty())
		{
			// Primeira varredura:
			for (short i = 0; i < Container.size(); ++i)
			{
				if (Container[i].item->name == _item->name)
				{
					short count = 0;

					// Limitando 'amount' ao somatório dos itens identicos -->
					for (short j = 0; j < Container.size(); j++)
					{
						if (Container[j].item->name == _item->name)
						{
							count += Container[j].amount;
						}
					}

					if (amount > count)
					{
						amount = count;
					}
					/* <-- Limitando 'amount' ao somatório dos itens identicos
					
					Gerenciamento de Itens --> */
					while (amount > Container[i].item->stack)
					{
						amount -=  Container[i].item->stack;
						Container.erase(Container.begin() + i);
						i--;
						input = '\0';
						index = 0;
						hoveredSlot = nullptr;
						selectedSlot = nullptr;
					}

					if (amount <= Container[i].amount)
					{
						Container[i].amount -= amount;

						if (Container[i].amount == 0)
						{
							Container.erase(Container.begin() + i);
							i--;
							input = '\0';
							index = 0;
							hoveredSlot = nullptr;
							selectedSlot = nullptr;
						}
					}
					if (!_usingItem)
					{
						std::cout << "\n";
						Renderer::Dialog(_item->name + " has been discarded.");
						if (_getch());
					}
					return;
				}
			}
		}
		
		return;
	}
}

void Inventory::OrganizeSlots()
{
	if (Container.size() > 0)
	{
		if (organize)
		{
			if (selectedSlot == nullptr) // Seleciona um item;
			{
				selectedSlot = hoveredSlot;
				hoveredSlot = nullptr;
			}

			else // Caso Enter novamente, troca o slot/item selecionado pelo hovered atual.
			{
				std::iter_swap(Container.begin() + GetSlotIndex(selectedSlot), Container.begin() + GetSlotIndex(hoveredSlot));
				selectedSlot = nullptr;
			}
		}
	}
}

std::shared_ptr<Item> Inventory::Initialize()
{
	active = true;

	while (active)
	{
		system("cls");
		std::cout << "\n";
		std::cout << " | |ESC| RETURN" << "\n";
			
		organize ? 
		std::cout << " | |TAB| Organize [X]" : 
		std::cout << " | |TAB| Organize [ ]";
		std::cout << "\n";
		std::cout << "\n";

		if (Container.size() == 0)
		{
			input = '\0';
			index = 0;
			hoveredSlot = nullptr;
			if (_getch());
			return nullptr;
		}

		hoveredSlot = std::make_shared<Slot>(Container[index]);

		#pragma region ITEM_DESCRIPTION
		if (hoveredSlot)
		{
			if (std::dynamic_pointer_cast<Equipment>(hoveredSlot->item))
			{
				std::cout << " | [Equipment] " << hoveredSlot->item->description << "\n";
			}
			else
			{
				std::cout << " | [Item] " << hoveredSlot->item->description << "\n";
			}
		}
		std::cout << "\n";
		#pragma endregion

		for (int i = 0; i < Container.size(); ++i)
		{
			// Indicador: HOVERED
			if (i == index)
			{
				if (std::shared_ptr<Equipment> equip = std::dynamic_pointer_cast<Equipment>(Container[i].item))
				{
					equip->equiped ?
						std::cout << " | > " << Container[i].item->name << " [Equipped]" :
						std::cout << " | > " << Container[i].item->name;
				}
				else
				{
					std::cout << " | > " << Container[i].amount << " x " << Container[i].item->name;
				}
			}
			else
			{
				if (std::shared_ptr<Equipment> equip = std::dynamic_pointer_cast<Equipment>(Container[i].item))
				{
					equip->equiped ?
						std::cout << " |   " << Container[i].item->name << " [E]":
						std::cout << " |   " << Container[i].item->name;
				}
				else
				{
					std::cout << " |   " << Container[i].amount << " x " << Container[i].item->name;
				}
			}

			if (selectedSlot)
			{
				if (selectedSlot->item->name == Container[i].item->name)
				{
					std::cout << " <";
				}
			}

			std::cout << "\n";
		}

		input = _getch();

		switch (input)
		{
			case 'w': case 'W':
				if (index > 0) index--; 
				break;

			case 's': case 'S':
				if (index < Container.size() - 1) index++; 
				break;

			case '\t': 
				organize = !organize; 
				break;
			
			case '\r':
			{
				if (organize)
				{
					OrganizeSlots();
				}

				else 
				{
					if (hoveredSlot)
					{
						return hoveredSlot->item;
					}
					else
					{
						return nullptr;
					}
				}
			}
			break;
			
			case 27: case 'i': case 'I':
			{
				active = false;
				selectedSlot = nullptr;
				return nullptr;
			}
		}
	}
}