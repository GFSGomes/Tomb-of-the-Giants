#pragma once
#include "Equipment.hpp"

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

	Armor(ArmorType, Sprite, const char*, const char*, float, float, float, float, short, short, short, short, short);
	~Armor();
};