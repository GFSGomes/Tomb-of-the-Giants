#include "Inventory.hpp"
#include <limits>

Inventory::Inventory() : Container{}, hoveredSlot{nullptr}, selectedSlot{nullptr}, organize{false}, remove{false}
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
				// Se houver Item no inventário:
				if (Container[i].item->name == _item->name)
				{
					for (short j = 0; j < Container.size(); j++)
					{
						// Encontra um Slot não-cheio, para adicionar o restante de _amount:
						if (Container[j].amount < Container[j].item->stack)
						{
							Container[j].amount += _amount;

							// Se o restante de _amount ultrapassar o _item.stack,
							// preenche-o e cria um novo Slot com o restante.
							if (Container[j].amount + _amount > Container[j].item->stack)
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

								if (Container[j].amount + _amount >= Container[j].item->stack)
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

void Inventory::DiscardItem(std::shared_ptr<Item> _item)
{
	std::cout << "\n";
	std::cout << "   How many " << _item->name << " do you want to discard?" << "\n";
	std::cout << "   > ";

	short amount;

	while (true)
	{
		std::cin >> amount;

		if (!std::cin)
		{
			std::cout << "   Please, enter a integer:" << std::endl;
			std::cout << "   > ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		if (!Container.empty())
		{
			for (int i = 0; i < Container.size(); i++)
			{
				if (Container[i].item->name == _item->name)
				{
					if (Container[i].amount > amount)
					{
						Container[i].amount -= amount;
						return;
					}

					if (Container[i].amount <= amount)
					{
						index = 0;
						Container.erase(Container.begin() + i);
					}
				}
			}
			Container.shrink_to_fit();
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

void Inventory::Initialize()
{
	active = true;

	while (active)
	{
		system("cls");

			std::cout << "\n";
			std::cout << "   [ESC] RETURN" << "\n";
			
		organize ? 
			std::cout << "   [TAB] Organize (X)" : 
			std::cout << "   [TAB] Organize ( )";
		remove ? 		     
			std::cout << "   [BKS] Remove (X)" : 
			std::cout << "   [BKS] Remove ( )";

			std::cout << "\n";
			std::cout << "\n";

		for (int i = 0; i < Container.size(); i++)
		{
			// Indicador: HOVERED
			if (i == index)
			{
				hoveredSlot = std::make_shared<Slot>(Container[index]);

				std::cout << "  > ";
			}
			else
			{
				std::cout << "    ";
			}

			std::cout << "" << Container[i].item->name << " (" << Container[i].amount << ")";

			// Indicador: SELECTED
			if (std::make_shared<Slot>(Container[index]) == selectedSlot)
			{
				std::cout << " <\n";
			}
			else
			{
				std::cout << "\n";
			}
		}
		if (selectedSlot)
		{
			std::cout << "    S:";
			std::cout << selectedSlot->item->name << "\n";
		}

		input = _getch();

		switch (input)
		{
			case 'w': if (index > 0) index--; break;
			case 's': if (index < Container.size() - 1) index++; break;
			case '\t': organize = !organize; remove = false; break;
			case '\b': remove = !remove; organize = false; break;
			case '\r':
			{
				if (remove)
				{
					DiscardItem(hoveredSlot->item);
				}

				if (organize)
				{
					OrganizeSlots();
				}
				else
				{
					// Equipar / Usar
				}

			}
			break;
			
			case 27: 
				active = false;
				selectedSlot = nullptr;
				break;

			default: break;
		}
	}
}