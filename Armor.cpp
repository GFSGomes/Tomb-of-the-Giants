#include "Armor.hpp"
//#include "Renderer.hpp"

Armor::Armor(ArmorType _armorType, Sprite _sprite, const char* _name, const char* _description = "\0", float _physical_resistance, float _magical_damage, float _dodge, float _flee, short _STR, short _CON, short _INT, short _AGI, short _DEX) :
	armorType{_armorType},
	bonusSTR{_STR}, bonusCON{_CON}, bonusINT{_INT}, bonusAGI{_AGI}, bonusDEX{_DEX},
	physical_resistance{_physical_resistance}, magical_resistance{_magical_damage},
	dodge{_dodge}, flee{_flee},
	Equipment(_name, EquipmentClass::ARMOR)
{
	sprite = _sprite;
	description = _description;
}

Armor::~Armor(){
}