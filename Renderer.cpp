#include "Renderer.hpp"
#include "Global.hpp"
#include <Windows.h> // Sleep
#include <conio.h>   // _getch()
#include <iomanip>   // conversões de precisão
#include <iostream>  // cout / cin
#include <vector>    // cout / cin

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

void Renderer::Dialog(std::string _text, short _read_speed)
{
    short index = 0;
    std::cout << " | ";
    
    while (true)
    {
        std::cout << _text[index];

        Sleep(_read_speed);

        if (index == _text.length())
        {
            if (_kbhit())
            {
                for (short i = index; i < (_text.length() - index); i++)
                {
                    std::cout << _text[i];
                }
            }
            break;
        }
        index++;
    }
    /*char temp[254];

    short count = 0;
    const char* text = _text.c_str();

    strncpy_s(temp, text, 255);
    
    std::cout << " | ";
   
    while (true)
    {
        Sleep(_read_speed);
        std::cout << temp[count];

        if (count == strlen(temp) || _getch())
        {
            if (_getch())
            {
            }
            break;
        }
        count++;
    }*/
}

void Renderer::StatusBar(const char* _bar_name, float _cur_value, float _max_value)
{
    std::setprecision(0);

    short barLength = 20;
    short barUnit = 100 / barLength;

    if (CompatibilityMode)
    {
        float pct = (_cur_value / _max_value) * 100;
        
        std::cout << " | " << _bar_name << ": " << " <";

        for (short i = 0; i < barLength; i++)
        {

            if (pct > i * barUnit)
            {
                std::cout << "=";
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << "> " << pct << "%" << "\n";
    }
    else
    {
        float pct = (_cur_value / _max_value) * 100;
        
        std::cout << " | " << _bar_name << " |";

        for (short i = 0; i < barLength; i++)
        {

            if (pct > i * barUnit)
            {
                std::cout << "■";
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << "| " << _cur_value << " (" << pct << "%)" << "\n";
    }
}

void Renderer::DisplaySprite(Sprite _sprite)
{
    switch (_sprite)
    {
        case Sprite::OH_SWORD:{
            std::cout << R"(
              _
             {o}
             ]'[
           ._]_[_.
           \.+-+./
             |||
             |||
             |||
             |'|
             | |
             | |
             \ /
              '
)";
        
        } break;
        case Sprite::TH_SWORD:{
            std::cout << R"(
             .
            / \
            | |
            | |
            | |
            | |
            | |
            | |
            |.|
            |||
            |||
         .__|||__.
         '--.^.--'
            ] [
            ] [
            ] [
            (_)
)";
        
        } break;
        case Sprite::OH_AXE:{
            std::cout << R"(
             .-.    ___
         .---+=+---''//
          '''+=+-.  //
             [ ]  \//
             | |   '
             | |
             | |
             | |
             [']
             ) (
             ) (
             [_]
)";
        } break;
        case Sprite::TH_AXE: {
            std::cout << R"(
                         ____
         ____    []     /  //
         \\ '--'_||_'--'   //
         \\    - == -      //
         \\    .-++--.    //
          \\_/   ||   )  //
           \/    ||   \_//
                 ||    \/
                 ||
                 ||
                 ||
                 []
                 ][
                 ][
                 ][
                 ][
                 ][
                 ][
                 []
)";
        } break;
        case Sprite::Falchion: {
            std::cout << R"(
             /'
 .--.       ||_______...........-'-.....:'/
|    |''''''||-------------------------'.'
 '--''''''''||---------.....______..--'
           ./
)";
        } break;
        case Sprite::Rapier: {
            std::cout << R"(
            \()
             ][
             ][\
          o==()/=o
            'TT'
             ||
             ||
             ||
             ||
             ||
             ||
             ||
             ||
             ||
             ||
             '/
)";
        } break;
        case Sprite::DAGGER:{
            std::cout << R"(
             (o)
             ] [ 
           ._]_[_.
          '.-+ +-.'
             |T|
             |||
             |||
             |||
             |//
             |/
)";
            break;
        }
        case Sprite::BOW: {
            std::cout << R"(
               .
             //
            ((
           / \\
          /   \\
         /    //
        /    /(
       /    //'
      /    /(
     /____//
    //'''''
    '
)";
        } break;
        case Sprite::LIGHT_BODY: {
            std::cout << R"(
        ___--''--___
    _.-'\  '-__-'  /'-._
    \   /          |   /
     \-'|      /   |'-/
        |   _-'    |
        |       /  |
        )_\___//___(
        ]:_:_[]_:_:[
        /  /'  \   \
        '-------'--'  
)";
           
        } break;
        case Sprite::MEDIUM_BODY:{
            std::cout << R"(
          __.-----.__
        ///\____.-'/  \
       //\  /\  /\|    \
      / | \/  \/  \     \
     (  | /\  /\  /\     )
      '-|/  \/  \/  \__-'
        \\__/\__/\__//
        )[][__][]___(
        | /\\/  \/  \\
        |/  \\  /\  /|
        |\__/\\/__\/-|
        \__/  \____-'
)";
           
        } break;
        case Sprite::HEAVY_BODY:{
            std::cout << R"(
          __.-----.__
         / \____.-'/ \
        /   /     |   | 
       /   /       \__/
       |             /
       \            /
        \          /\
        /'        ' /
        '-________-'
)";
            
        } break;
        case Sprite::LIGHT_HEAD: {
            std::cout << R"(
            _____
           /     \
          /.---.  \
         //     '-.\
        //         \\
        \\  -===-  //
      .-'\\__/T\__//'-.
      '-._    |    _.-'
          '-./ \.-'
)";
        } break;
        case Sprite::MEDIUM_HEAD: {
            std::cout << R"(
         .-|'|-.
       /'  | |  '\
      /____|+|____\
     |_____|+|_____|
      |\< >|+|< >/|
      ||'--|_|--'||
      \|         |/
)";
        } break;
        case Sprite::HEAVY_HEAD: {
            std::cout << R"(
           _.--+-+-._
         .'          \
       /'---..___     \
      ///.    .-.\    /
      \\\\\   '-'/   /
       \\\'_.---'_ _/
        \.'  \_____-'
       
)";
        } break;
        case Sprite::TORCH: {
            std::cout << R"(
            '(.
           (._)\'
           ')  (,
            \{}/
             []
             ||
             ||
             ||
             ||
             ||
             []
)";
        } break;
        case Sprite::MINOR_HEALTH_POTION:{
            std::cout << R"(
            _
           ]-[
          /---\
          \___/
)";

        } break;
        case Sprite::MEDIUM_HEALTH_POTION: {
            std::cout << R"(
            _
           ]-[
          /---\
          |   |
          \___/
)";

            
        }break;
        case Sprite::GREATER_HEALTH_POTION:{
            std::cout << R"(
            _
           ]-[
          /---\
         /     \
         \_____/
)";

            
        } break;
        case Sprite::MINOR_MANA_POTION:{
            std::cout << R"(
            _
           ]-[
          /---\
          \___/
)";

            
        }break;
        case Sprite::MEDIUM_MANA_POTION:{
            std::cout << R"(
            _
           ]-[
          /---\
          |   |
          \___/
)";
        }break;
        case Sprite::GREATER_MANA_POTION:{
            std::cout << R"(
            _
           ]-[
          /---\
         /     \
         \_____/
)";

            
        } break;
        case Sprite::CANDLE: {
            std::cout << R"(
            # # # # # # # #   
        # # # # # # # # # # # #  
      # # # # + + + + + + # # # #  
      # # + + + - - - - + + + # #  
    # # # + + - - - - - - + + # # # 
    # # + + - - -     - - - + + # # 
    # # + + - -   .(    - - + + # # 
    # # + + - -   (.)'  - - + + # # 
    # # + + + - - [ ] - - + + + # # 
    # # # + + + - | | - + + + # # # 
      # # + + + + | | + + + + # # 
      # # # # + + | | + + # # # # 
        # # # # # | | # # # # #  
            # # # |_| # # #
)";
        } break;
        case Sprite::KEY_0:{
            std::cout << R"(
             __
            //\\
           ((  ))
            \\//
             ||
             ||
             ||-.
             ||(
             ||-'
)";
        } break;
        case Sprite::KEY_1:{
            std::cout << R"(
            ____
           / __ \
           \(  )/
            \\//
             ||
             ||
             ||-.
             ||[
             ||-'
)";
        } break;
        case Sprite::KEY_2:{
            std::cout << R"(
          .------.
          |--[]--|
          |__  __|
             ||
             ||
             ||-.
             || |
             ||-'
)";
        } break;
        case Sprite::SKELETON_GIANT:{
            std::cout << R"(
                     -.           
     .-~~~-.        /  '~..__..-~;
    / .   . \      /           | |
    |\_\ /_/|      \-..._      / /
    )(.) (.)(   _.-/ /---.   ,' / 
    \_. " ._/  /-~-\/     \,' ,'  
     ||-~-||   /''\\\     | ,'    
     \\___//   `/`\\\\    '`      
      \'''/    / / (  )           
       '-'    / /                 
)";
        } break;
        case Sprite::SKELETON_FOOTMAN:{
            std::cout << R"(
            .-~-.      
           /     \     
           )'. .'(     
           (<>.<>)     
            )...(      
         .-~\'''/~-..  
       /  .__..-"-.;__\
      / / |     /'7   |
     / /  |    / /    |
    { (   \   / /     /
)";

        } break;
        case Sprite::SPIDER:{
            std::cout << R"(
            .  .
         . / __ \ .
          \\(||)//
         /'.(::).'\
        '  \ "" /  '
           '    '
)";

        } break;
        case Sprite::TITLE:{
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
        case Sprite::DEATH: {
            std::cout << R"(    
                                           .--.   _.._______         
                                          /--.'\  \..------._\       
                                          \   \/\  ||        '       
                                          /      \ ||                
                                         /\    |  \||                
                                         ||    |/ _||                
                                         ||    | /'+:                
                                         ||     \_/||                
                _[]_                     \|    \   ||                   
               // /\\                     |       \||                 
              /// \ \\.____               |    \   ||\                      
              _/   \  '                  /|     \  ||\                
             /__/\_/                     \|        ||/                
            \(   /(_                      \_.-.__./||
)";
        } break;
    }
}