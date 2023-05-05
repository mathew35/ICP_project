/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/
#include "Door.h"

Door::Door(int row, int col, GameInterface* o, Logger* logger, int keys = 0)
{
	this->open = false;
	this->logger = logger;
	this->row = row;
	this->col = col;
	this->observer = o;
	this->keys = keys; //TODO fix keys count
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
		logger->printDoor(this->row, this->col);
		observer->notifyOpenDoors(this->row, this->col);
	}
}
