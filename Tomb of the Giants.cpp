#include "Potion.hpp"
#include "Inventory.hpp"

int main()
{
	Inventory inv;

	Potion* healthPotion = new Potion("Health Potion");
	Potion* manaPotion = new Potion("Mana Potion");
	Potion* perceptionPotion = new Potion("Perception Potion");

	inv.AddItem(perceptionPotion, 1);
	inv.AddItem(healthPotion, 5);
	inv.AddItem(manaPotion, 6);

	inv.Initialize();
}