#include "GameObject.hpp"

GameObject::GameObject() : name{'\0'}, description{'\0'}, posX{0}, posY{0}, active{true}, sprite{Sprite::NONE}
{

}

GameObject::~GameObject() 
{

}

void GameObject::SpawnAt(short _posX, short _posY) 
{
	posX = _posX;
	posY = _posY;
}

void GameObject::SpawnRandom()
{
	posX = rand() % GridSizeX;
	posY = rand() % GridSizeY;
}