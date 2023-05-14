#pragma once
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include "Global.hpp"
#include <conio.h>

enum class Sprite {
    NONE,
    OH_SWORD, OH_AXE, TH_SWORD, TH_AXE, DAGGER, BOW, STAFF,
    HEAVY_BODY, MEDIUM_BODY, LIGHT_BODY, HEAVY_HEAD, LIGHT_HEAD,
    TORCH, POTION,
    SKELETON_FOOTMAN, SKELETON_GIANT, SPIDER, GHOUL,
    TITLE,
    DEATH,
    ANI_0, ANI_1, ANI_3
};

struct Renderer 
{
    Renderer();
    ~Renderer();

    static void Dialog(std::string);
    static void StatusBar(const char*, float, float);
    static void DisplaySprite(Sprite);
};