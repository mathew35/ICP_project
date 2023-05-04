/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/
#include "Door.h"

Door::Door(int row, int col, GameInterface* o, int keys = 0)
{
	this->row = row;
	this->col = col;
	this->observer = o;
	this->keys = keys;
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
	if (observer->getKeys().size() == keys)
	{
		open = true;
	}
}
