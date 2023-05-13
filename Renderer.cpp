#pragma once
#include "Renderer.hpp"

//bool CompatibilityMode;

Renderer::Renderer() {

}

Renderer::~Renderer() {

}


void Renderer::Dialog(std::string _text)
{
    char temp[255];
    short count = 0;
    const char* text = _text.c_str();

    strncpy_s(temp, text, 255);
    
    std::cout << " | ";
   
    while (true)
    {
        Sleep(5);
        std::cout << temp[count];

        if (count == strlen(temp) || _kbhit())
        {
            break;
        }
        count++;
    }
}

void Renderer::StatusBar(const char* _bar_name, float _cur, float _max)
{
    std::setprecision(0);

    short barLength = 10;
    short barUnit = 100 / barLength;

    if (CompatibilityMode)
    {
        float pct = (_cur / _max) * 100;
        
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
        float pct = (_cur / _max) * 100;
        
        std::cout << " | " << _bar_name << ": ";

        for (short i = 0; i < barLength; i++)
        {

            if (pct > i * barUnit)
            {
                std::cout << "■";
            }
            else
            {
                std::cout << "□";
            }
        }
        std::cout << " " << pct << "%" << "\n";
    }
}

void Renderer::DisplaySprite(Sprite _sprite) {

	switch (_sprite) {
        case Sprite::NONE:
        {
            
        } break;

        // EQUIPMENT:
        case Sprite::OH_SWORD:
        {
            std::cout << R"(
             .
            / \
            | |
            | |
            | |
            |.|
            |||
            |||
         .__|||__.
         '--.^.--'
            ] [
            (_)
)";
        } break;

        case Sprite::OH_AXE:
        {
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


        // ITEMS:
        case Sprite::TORCH:
        {
            std::cout << R"(
            '(.
           (._)\'
           ')  (,
            \{}/
             []  You found a Torch.
             ||  ...
             ||  
             ||  Even in the darkest places,
             ||  you can find a spark of hope.
             []
)";
        } break;

        case Sprite::POTION:
        {
            std::cout << R"(
            .-.
            |-|
          .-' '-.
         /_______\
        |         |
         \       /
          '-----'
)";
        } break;

        // MONSTERS
        case Sprite::SKELETON_GIANT:
        {
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

        case Sprite::SKELETON_FOOTMAN:
        {
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

        case Sprite::SPIDER:
        {
            std::cout << R"(
            .  .
         . / __ \ .
          \\(||)//
         /'.(::).'\
        '  \ "" /  '
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

        case Sprite::DEATH:
        {
            std::cout << R"(                                  
                                                            
                                    .--.   _.._______         
                                   /--.'\  \..------._\       
                                   \   \/\  ||        '       
                                   /      \ ||                
                                  /\    |  \||                
                                  ||    |/ _||                
                                  ||    | /'+:                
                                  ||     \_/||                
                _[]_              \|    \   ||                   
               // /\\              |       \||                 
              /// \ \\.____        |    \   ||\                      
              _/   \  '           /|     \  ||\                
             /__/\_/              \|        ||/                
            \(   /(_               \_.-.__./||                 
                                                               
 
|   DEATH                                                      |
|  ----------------------------------------------------------  |
|   How sad.                                                   |
|                                                              |
|   Now, you are one of them... draggin a weapon to and fro.   |
|   I can't reap your soul. The Tomb of the Giants is          |
|   out of my domains.                                         |
|                                                              |
|   ...                                                        |
|   There is no "rest in peace" for you...                     |
|                                                              |)";
        } break;
	}
}

        //    std::cout << R"(
        //  .--------.
        // /          \
        //|\          /|
        //|/____\/____\|
        ///(___/  \___)\
        //\__   ''   __/
        // | '++++++' |
        //  \'++++++'/
        //   '-____-'
        //              )";

         //   std::cout << R"(
         //   .    .
         //. /      \ .
         //| | /""\ | |
         //\ \(    )/ /
         // \_\\__//_/
         // / //  \\ \
         //| | \::/ | |
         //' \  ""  / '
         //   '    '
         //            )";

        // std::cout << R"(
        //   /\
        //  |  |
        //  |  |
        //  |  |
        //  |  |
        //  |  |
        //  |  |
        //  |/\|
        //  ))((
        //  \\//
        //[//[]//]
        //   ||
        //   ||
        //   []
        //        )";

         //   std::cout << R"( 
         //     []     ____
         //.--'_||_'--'  //
         //| -==[]===-   //
         //\  .-||--.    //
         // \(  ||   )  //
         //  '  ||   \ //
         //     ||    \/
         //     ||
         //     ||
         //     []
         //     ][
         //     ][
         //     ][
         //     []
         //                )";

//            -.
//____________||_____
//\ `~~~------||_____[)
// `"~~-------\*.___.-.
//             `~---~*'


	  // .-~~~-.
	  /// .   . \
	  //|\_\ /_/|      -.
	  //)(.) ( )(     /  '~..__..-~;
	  //\_. " ._/    /           | |
	  // ||-~-||     \-..._      / /
	  // \\___//  _.-/ /---.   ,' /
	  //  \'''/  /-~-\/     \,' ,'
	  //   '-'   /''\\\     | ,'
	  //         `/`\\\\    '`
	  //         / / (  )
	  //        / /
	  //       / /