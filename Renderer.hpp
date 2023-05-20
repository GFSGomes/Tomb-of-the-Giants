#pragma once
#include <iostream>

enum class Sprite {
    NONE,
    OH_SWORD, OH_AXE, TH_SWORD, TH_AXE, DAGGER, BOW, STAFF,
    HEAVY_BODY, MEDIUM_BODY, LIGHT_BODY, HEAVY_HEAD, LIGHT_HEAD,
    TORCH, CANDLE, KEY_0, KEY_1, KEY_2,
    MINOR_HEALTH_POTION, MEDIUM_HEALTH_POTION, GREATER_HEALTH_POTION,
    MINOR_MANA_POTION, MEDIUM_MANA_POTION, GREATER_MANA_POTION,
    SKELETON_FOOTMAN, SKELETON_GIANT, SPIDER, GHOUL,
    TITLE,
    DEATH,
    ANI_0, ANI_1, ANI_3
};

struct Renderer 
{
    Renderer();
    ~Renderer();

    static void Dialog(std::string, short _read_speed = 5);
    static void StatusBar(const char*, float, float);
    static void DisplaySprite(Sprite);
};