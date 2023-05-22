#include "Wall.hpp"

Wall::Wall(short _startX, short _startY) : direction{}
{
	posX = _startX;
	posY = _startY;
}

Wall::Wall(WallDirection _walldirection, short _startX, short _startY, short _lenght) : direction{_walldirection}
{
	posX = _startX;
	posY = _startY;

	for (short i = 0; i < _lenght; i++)
	{
		switch (_walldirection)
		{
			case WallDirection::HORIZONTAL:
				bricks.push_back(std::make_shared<Wall>(posX + i, posY));
				break;

			case WallDirection::VERTICAL:
				bricks.push_back(std::make_shared<Wall>(posX, posY + i));
				break;
		}
	}
}

Wall::~Wall()
{

}