#pragma once
#include <vector>
#include <memory>

enum class Class
{
	WARRIOR, ARCHER, ROGUE, WIZARD
};

struct Archetype
{
	Class name;

	Archetype(Class);
	~Archetype();

	private:
	void SetSkillTree();
};