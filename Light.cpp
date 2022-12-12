#include "Light.hpp"

Light::Light() : proximityReveal{false}
{

}

Light::~Light()
{

}

void Light::Reposition(short x, short y)
{
	posX = x;
	posY = y;
}