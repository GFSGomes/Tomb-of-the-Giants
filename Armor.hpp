#pragma once
#include "Equipment.hpp"

enum class Sprite;

enum class ArmorType
{
	BODY, HEAD, ARMS, LEGS
};

struct Armor : Equipment
{
	ArmorType armorType;

	short bonusSTR;
	short bonusCON;
	short bonusINT;
	short bonusAGI;
	short bonusDEX;

	float physical_resistance;
	float magical_resistance;
	float dodge;
	float flee;

	Armor(ArmorType armor_type, Sprite armor_sprite, const char* name, const char* description, float physical_resistance = 0,
		float magical_resistance = 0, float dodge = 0, float flee = 0, 
		short STR = 0, short CON = 0, short INT = 0, short AGI = 0, short DEX = 0);
	~Armor();
};