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

short Inventory::DiscardItem(std::shared_ptr<Item> _item, short _amount, bool _usingItem)
{
	active = true;
	short confirmation_index = 0;
	bool confirmation_active = true;
	char confirmation_input = '\0';
	short discardedAmout{0};

	short amount = _amount;

	while (active)
	{
		if (_amount == 0)
		{
			system("cls");
			std::cout << "\n";
			std::cout << " | " << _item->name << "\n";
			Renderer::DisplaySprite(_item->sprite);
			std::cout << "\n";
			std::cout << " | [?] How many " << _item->name << " do you'd like to discard?" << "\n";
			std::cout << " | > Amount:  " << amount << "\n";

			switch (_getch())
			{
				case 'w': case 'W': amount += 10; continue;
				case 's': case 'S': if (amount >= 10) amount -= 10; continue;
				case 'a': case 'A': if (amount > 0) amount--; continue;
				case 'd': case 'D': amount++; continue;
				
				case 27:  // Esc
					active = false; 
					return 0;
				
				case '\r': // Enter
				{
					if (amount == 0)
					{
						active = false;
						return 0;
					}
					break;
				}
			}
		}

		// Confirmação
		while (confirmation_active && !_usingItem)
		{
			system("cls");
			std::cout << "\n";
			std::cout << " | [!] " << _item->name << " will be discarded:" << "\n";
			Renderer::DisplaySprite(_item->sprite);
			std::cout << "\n";
			std::cout << " | Are you sure?" << "\n";
			std::cout << " | " << "\n";

			switch (confirmation_index)
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

			confirmation_input = _getch();

			switch (confirmation_input)
			{
				case 'w': case 'W':
				{
					if (confirmation_index > 0) confirmation_index--;
					break;
				}
				case 's': case 'S':
				{
					if (confirmation_index < 1) confirmation_index++;
					break;
				}
				case '\r':
				{
					switch (confirmation_index)
					{
						case 0: confirmation_active = false; continue;
						case 1:
						{
							active = false;
							confirmation_active = false;
							return 0;
						}
					}
				}
				case 27:
				{
					active = false;
					confirmation_active = false;
					return 0;
				}
			}
		}

		if (!Container.empty())
		{
			short count{0};

			// Primeira varredura:
			for (short i = 0; i < Container.size(); ++i)
			{
				if (Container[i].item->name == _item->name)
				{
					// Limitando 'amount' ao somatório dos itens identicos -->
					for (short j = 0; j < Container.size(); j++)
					{
						if (Container[j].item->name == _item->name)
						{
							count += Container[j].amount;
						}
					}

					if (amount >= count)
					{
						amount = count;
						discardedAmout = amount;
					}
					/* <-- Limitando 'amount' ao somatório dos itens identicos
					
					Gerenciamento de Itens --> */
					while (amount > Container[i].item->stack)
					{
						amount -=  Container[i].item->stack;
						Container.erase(Container.begin() + i);
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
					return discardedAmout;
				}
			}
		}
		
		return discardedAmout;
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