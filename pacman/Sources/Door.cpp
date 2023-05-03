/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/
#include "Door.h"

Door::Door(int row, int col, GameInterface* o)
{
	this->row = row;
	this->col = col;
	this->observer = o;
}

Door::~Door()
{
}

bool Door::isOpen()
{
	return open;
}

void Door::openDoors()
{
	if (observer->getKeys == nullptr)
	{
		openn = true;
	}
}
