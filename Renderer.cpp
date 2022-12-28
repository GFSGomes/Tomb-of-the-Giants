#pragma once
#include "Renderer.hpp"

Renderer renderer;

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

void Renderer::DisplaySprite(Sprite _sprite) {

	switch (_sprite) {
        case Sprite::NONE: break;

        // EQUIPMENT:
        case Sprite::OH_SWORD:
        {
            std::cout << R"(
              /\
             |  |
             |  |
             |  |
             |  |
             |  |
             |  |
             |/\|
             ))((
             \\//
           [//[]//]
              ||
              ||
              []
                   )";
        } break;

        case Sprite::OH_AXE:
        {
            std::cout << R"( 
              []     ____
         .--'_||_'--'  //
         | -==[]===-   //
         \  .-||--.    //
          \(  ||   )  //
           '  ||   \ //
              ||    \/
              ||
              ||
              []
              ][
              ][
              ][
              []
                         )";
        } break;


        // ITEMS:
        case Sprite::TORCH:
        {
            std::cout << R"(
               ,      
             '(.
            (._)\' 
            ')  (,
             \{}/
              []
              []
              []
              ||
              []
              ||
              ||
              ||
              []
                  )";
        } break;

        // MONSTERS
        case Sprite::SKULL:
        {
            std::cout << R"(
          .--------.
         /          \
        |\          /|
        |/____\/____\|
        /(___/  \___)\
        \__   ||   __/
         | '++++++' |
          \'++++++'/
           '-____-'
                      )";
        } break;

        case Sprite::SPIDER:
        {
            std::cout << R"(
            .    .
         . /      \ .
         | | /""\ | |
         \ \(    )/ /
          \_\\__//_/
          / //  \\ \
         | | \::/ | |
         ' \  ""  / '
            '    '
                     )";
        } break;

        // SYMBOLS

        case Sprite::TITLE:
        {
            std::cout << R"(
                                   ____     __
                                   \\  '--'_||_'--.
     \\''||'''''//          //'    \\   -===[]==- |
         ||        ||'\\'\\ ||'\\  \\    .--::-.  /
         ||  //'\\ || || || || ((   \\  (   ||  )/
         ||  )) (( || || || ||.//    \\ /   ||  '
         ||  \\.// |/ '               \/    ||
         ||          //'  ||  //'           ||
         \\.  //'\\ '||'  ||' ||'\\ //'\\   ||
              )) ((  ||   ||  || (( ))//'   ||
     //''''\\ \\.//  ||   \\  || // \\.//   []
     ||     '                               ][
     ||    \\ '' //''\\ ||''\\ ||  //''\\   ][
     ||    || || '   || ||  || ||' ||   '   ][
     ||    || || //''|| ||  || ||  \\--\\   ][
     ||    || || ||  || ||  || ||  .   ||   ][
     \\....// \\ \\..\\ ||  || \\. \\..//   []
)";
        } break;

        // ICONS
        case Sprite::ICON_TARGET:
        {
            std::cout << R"(
              \/
              /\
                )";
        } break;

        case Sprite::ICON_SWORD:
        {
            std::cout << R"(
           -====|=-
                   )";
        } break;

        case Sprite::ICON_AXE:
        {
            std::cout << R"(
           |(=====,
           '-'
                   )";
        } break;
	}
}