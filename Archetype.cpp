#include "Archetype.hpp"

Archetype::Archetype(Class _name = Class::WARRIOR) : _class{_name}
{
	SetSkillTree();
}

Archetype::~Archetype()
{

}

void Archetype::SetSkillTree()
{
	switch (_class)
	{
		case Class::WARRIOR:
			break;

		case Class::ARCHER:
			break;

		case Class::ROGUE:
			break;

		case Class::WIZARD:
			break;
	}
}

const char * Archetype::GetClassName()
{
	switch (_class)
	{
		case Class::WARRIOR:
			return "Warrior";

		case Class::ARCHER:
			return "Archer";

		case Class::ROGUE:
			return "Rogue";

		case Class::WIZARD:
			return "Wizard";
	}
}