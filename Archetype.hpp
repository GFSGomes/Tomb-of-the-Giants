#pragma once
#include <vector>
#include <memory>

struct Ability;

enum class Class
{
	WARRIOR, ARCHER, ROGUE, WIZARD
};

struct Archetype
{
	Class _class;
	//std::vector<Ability> ability;

	Archetype(Class);
	~Archetype();

	private:
	void SetSkillTree();
	const char * GetClassName();
};