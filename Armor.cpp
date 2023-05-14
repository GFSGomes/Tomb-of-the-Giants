#include "Armor.hpp"
/// <summary>
/// 
/// </summary>
/// <param name="_armorType"></param>
/// <param name="_name"></param>
/// <param name="_description"></param>
/// <param name="_STR"></param>
/// <param name="_CON"></param>
/// <param name="_INT"></param>
/// <param name="_AGI"></param>
/// <param name="_DEX"></param>
/// <param name="_physical_resistance"></param>
/// <param name="_magical_damage"></param>
/// <param name="_dodge"></param>
/// <param name="_flee"></param>
Armor::Armor(ArmorType _armorType, Sprite _sprite, const char* _name, const char* _description = "\0", float _physical_resistance = 0, float _magical_damage = 0, float _dodge = 0, float _flee = 0, short _STR = 0, short _CON = 0, short _INT = 0, short _AGI = 0, short _DEX = 0) :
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