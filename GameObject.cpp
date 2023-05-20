#include "GameObject.hpp"
#include "Global.hpp"
#include "Renderer.hpp"

GameObject::GameObject() : name{'\0'}, description{'\0'}, posX{-1}, posY{-1}, active{true}, force_spawn_at_zero{false}, sprite{Sprite::NONE}
{

}

GameObject::~GameObject() 
{

}

void GameObject::SpawnAt(short _posX, short _posY)
{
	if (_posX < 0) _posX = 0;
	if (_posY < 0) _posY = 0;

	posX = _posX;
	posY = _posY;
}

void GameObject::SpawnRandom()
{
	posX = rand() % (GridSizeX); // Parenteses são importantes
	posY = rand() % (GridSizeY); // Parenteses são importantes
}