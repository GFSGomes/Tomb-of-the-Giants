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

	Armor(ArmorType, Sprite, const char*, const char*, float _physical_resistance = 0,
		float _magical_resistance = 0, float _dodge = 0, float _flee = 0, 
		short _STR = 0, short _CON = 0, short _INT = 0, short _AGI = 0, short _DEX = 0);
	~Armor();
};