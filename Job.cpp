#include "Job.hpp"

Job::Job(Archetype _archetype) : archetype{_archetype}, JobSkills{}
{

}

Job::~Job()
{

}

std::string Job::GetJobName()
{
	std::string jobName;

	switch (archetype)
	{
		case Archetype::WARRIOR: jobName = "Warrior"; break;
		case Archetype::ARCHER: jobName = "Archer"; break;
		case Archetype::MAGE: jobName = "Mage"; break;
		case Archetype::ROGUE: jobName = "Rogue"; break;
		case Archetype::BARBARIAN: jobName = "Barbarian"; break;
	}

	return jobName;
}

void Job::DefineJobSkills()
{
	switch (archetype)
	{
		case Archetype::WARRIOR: 	
		{

		} break;

		case Archetype::ARCHER:
		{

		} break;
	}
}