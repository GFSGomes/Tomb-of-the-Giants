#include "Portal.hpp"
#include "Scene.hpp"

Portal::Portal(Position _position, std::shared_ptr<Scene> _scene, bool _isLocked, KeyType _keyType, short _posX, short _posY)
	: position{_position}, scene{_scene}, isLocked{_isLocked}, keyType{_keyType}, secretReveal{false}
{
    
}

Portal::~Portal()
{

}

void Portal::SearchMirrorInDestiny()
{
    // Defines this Portal mirror, by iterating through the portals in the destiny scene;
    // To set position, we need to look to the Mirror portal scene - which this portal is inside;
    for (std::shared_ptr<Portal> portal : scene->ScenePORTALs)
    {
        switch (position)
        {
            case Position::UP:
                if (portal->position == Position::DOWN)
                {
                    mirror = portal;
                    posX = mirror->scene->gridSizeX / 2;
                    posY = 0;
                }
                break;

            case Position::DOWN:
                if (portal->position == Position::UP)
                {
                    mirror = portal;
                    posX = mirror->scene->gridSizeX / 2;
                    posY = mirror->scene->gridSizeY - 1; // in Scene constructor: gridSizeN = grid.sizeN + 1;
                }
                break;

            case Position::LEFT:
                if (portal->position == Position::RIGHT)
                {
                    mirror = portal;
                    posX = 0;
                    posY = mirror->scene->gridSizeY / 2;
                }
                break;

            case Position::RIGHT:
                if (portal->position == Position::LEFT)
                {
                    mirror = portal;
                    posX = mirror->scene->gridSizeX - 1;
                    posY = mirror->scene->gridSizeY / 2;
                }
                break;

            case Position::UP_LEFT:
                if (portal->position == Position::DOWN_RIGHT)
                {
                    mirror = portal;
                    posX = 0;
                    posY = 0;
                }
                break;

            case Position::UP_RIGHT:
                if (portal->position == Position::DOWN_LEFT)
                {
                    mirror = portal;
                    posX = mirror->scene->gridSizeX - 1;
                    posY = 0;
                }
                break;

            case Position::DOWN_LEFT:
                if (portal->position == Position::UP_RIGHT)
                {
                    mirror = portal;
                    posX = 0;
                    posY = mirror->scene->gridSizeY - 1;
                }
                break;


            case Position::DOWN_RIGHT:
                if (portal->position == Position::UP_LEFT)
                {
                    mirror = portal;
                    posX = mirror->scene->gridSizeX - 1;
                    posY = mirror->scene->gridSizeY - 1;
                }
                break;

            case Position::CENTER:
                if (portal->position == Position::CENTER)
                {
                    mirror = portal;
                    posX = mirror->scene->gridSizeX / 2;
                    posY = mirror->scene->gridSizeY / 2;
                }
                break;

            case Position::OTHER:
                if (portal->position == Position::OTHER)
                {
                    mirror = portal;
                }
                break;
            
            default: break;
        }
    }

    if (mirror)
    {
        mirror->isLocked = isLocked;
        mirror->keyType = keyType;
    }
}