#pragma once
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include "Global.hpp"

enum class Sprite {
    NONE,
    OH_SWORD, OH_AXE, TH_SWORD, TH_AXE,
    TORCH, POTION,
    SKELENTON_FOOTMAN, SKELENTON_GIANT, SPIDER, GHOUL,
    TITLE,
    DEATH,
};

struct Renderer 
{
    Renderer();
    ~Renderer();

    static void Dialog(std::string);
    static void StatusBar(const char*, float, float);
    static void DisplaySprite(Sprite);
};