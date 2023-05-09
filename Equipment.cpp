#include "Equipment.hpp"

Equipment::Equipment(const char* _name, EquipmentClass _type) : equiped{false}, equipmentClass{_type}, Item(_name, 1)
{

}

Equipment::~Equipment()
{

}