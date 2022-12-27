#pragma once
#include "Ability.hpp"
#include <vector>
//#include "Weapon.hpp"

enum class Archetype
{
	WARRIOR, ARCHER, ROGUE, MAGE, BARBARIAN
};

struct Job
{
	Archetype archetype;
	std::vector<Skill> JobSkills;
	//std::vector<WeaponType> JobWeapons;

	Job(Archetype);
	~Job();

	public:
	std::string GetJobName();

	private:
	void DefineJobSkills();
};