#pragma once
#include <iostream>

enum class Sprite {
    NONE,
    OH_SWORD, OH_AXE,
    TORCH,
    SKULL, SPIDER,
    TITLE,
    ICON_TARGET, ICON_SWORD, ICON_AXE,
};

struct Renderer 
{
    Renderer();
    ~Renderer();

    void DisplaySprite(Sprite);
};

extern Renderer renderer;