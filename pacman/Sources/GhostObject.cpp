/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/

#include "GhostObject.h"


GhostObject::GhostObject(int row, int col, PathField* Field) {
	this->row = row;
	this->col = col;
	this->callerField = Field;
}

void GhostObject::setSurroundinFieldsGhost(Field* bottom, Field* right, Field* upper, Field* left, PathField* curPath) {
	this->bottomField = bottom;
	this->rightField = right;
	this->leftField = left;
	this->upperField = upper;
	this->callerField = curPath;
}

bool GhostObject::canMove(Field::Direction dir) {
	if (dir == Field::D && this->bottomField->canMove())
	{
		return true;
	}
	else if (dir == Field::R && this->rightField->canMove())
	{
		return true;
	}
	else if (dir == Field::U && this->upperField->canMove())
	{
		return true;
	}
	else if (dir == Field::L && this->leftField->canMove())
	{
		return true;
	}
	else
	{
		return false;
	}
}
Field* GhostObject::getField() {
	return this->callerField;
}
int GhostObject::getLives() {
	return 0;
}
bool GhostObject::move(Field::Direction dir) {
	//TODO move
	return true;
}
