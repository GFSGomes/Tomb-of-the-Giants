#include "Archetype.hpp"

Archetype::Archetype(Class _name = Class::WARRIOR) : name{_name}
{
	SetSkillTree();
}

Archetype::~Archetype()
{

}

void Archetype::SetSkillTree()
{
	Skilltree.clear();
	Skilltree.push_back(std::make_shared<Attack>(attack));

	switch (name)
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