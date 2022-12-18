#include "GameObject.hpp"

GameObject::GameObject() : name{"GameObject"}, posX{0}, posY{0}, active{false}
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