#pragma once
#include <vector>
#include <memory>
#include "AbilityDatabase.hpp"

enum class Class
{
	WARRIOR, ARCHER, ROGUE, WIZARD
};

struct Archetype
{
	Class name;
	std::vector<std::shared_ptr<Ability>> Skilltree;

	Archetype(Class);
	~Archetype();

	private:
	void SetSkillTree();
};