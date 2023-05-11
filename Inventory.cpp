#include "Inventory.hpp"

Inventory::Inventory() : active{false}, index{0}, input{'\0'}, Container{}, hoveredSlot{nullptr}, selectedSlot{nullptr}, organize{false}, remove{false}
{

}

Inventory::~Inventory()
{

}

void Inventory::AddItem(std::shared_ptr<Item> _item, short _amount = 1)
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
}

void Inventory::DiscardItem(std::shared_ptr<Item> _item, short _amount = 0)
{
	if (_amount == 0)
	{
		std::cout << "\n";
		std::cout << " | How many " << _item->name << " do you want to discard?" << "\n";
		std::cout << " | > ";
	}

	short amount = _amount;

	while (true)
	{
		if (_amount == 0)
		{
			std::cin >> amount;

			if (!std::cin)
			{
				std::cout << " | Please, enter a integer:" << std::endl;
				std::cin.clear();
				std::cout << " | > ";
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}
		}

		if (!Container.empty())
		{
			// Primeira varredura:
			for (short i = 0; i < Container.size(); i++)
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
					while (amount >= Container[i].item->stack)
					{
						amount -=  Container[i].item->stack;
						Container.erase(Container.begin() + i);
						input = '\0';
						index = 0;
						hoveredSlot = nullptr;
						hoveredSlot = nullptr;
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
						}
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
		remove ? 		     
		std::cout << "   |BKS| Remove [X]" : 
		std::cout << "   |BKS| Remove [ ]";
		std::cout << "\n";

		if (Container.size() == 0)
		{
			input = '\0';
			index = 0;
			hoveredSlot = nullptr;
			_getch();
			return nullptr;
		}

		hoveredSlot = std::make_shared<Slot>(Container[index]);

		std::cout << " |" << "\n";
		hoveredSlot ?
		std::cout << " |  >>> " << hoveredSlot->item->description << "\n" :
		std::cout << " |" << "\n";
		std::cout << " |" << "\n";

		for (int i = 0; i < Container.size(); ++i)
		{
			// Indicador: HOVERED
			if (i == index)
			{
				if (std::shared_ptr<Equipment> equip = std::dynamic_pointer_cast<Equipment>(Container[i].item))
				{
					if (equip->equiped)
					{
						std::cout << " | E> " << Container[i].item->name;
					}
					else
					{
						std::cout << " |  > " << Container[i].item->name;
					}
				}
				else
				{
					std::cout << " |  > " << Container[i].item->name << " (" << Container[i].amount << ")";
				}
			}
			else
			{
				if (std::shared_ptr<Equipment> equip = std::dynamic_pointer_cast<Equipment>(Container[i].item))
				{
					equip->equiped ?
						std::cout << " | E " :
						std::cout << " |   ";

					std::cout << Container[i].item->name;
				}
				else
				{
					std::cout << " |   " << Container[i].item->name << " (" << Container[i].amount << ")";
				}
			}

			std::cout << "\n";
		}

		input = _getch();

		switch (input)
		{
			case 'w': 
				if (index > 0) index--; 
				break;

			case 's': 
				if (index < Container.size() - 1) index++; 
				break;

			case '\t': organize = !organize; remove = false; break;
			case '\b': remove = !remove; organize = false; break;
			case '\r':
			{
				if (remove)
				{
					DiscardItem(hoveredSlot->item);
					break;
				}

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
			
			case 27: 
				active = false;
				selectedSlot = nullptr;
				break;
		}
	}
}