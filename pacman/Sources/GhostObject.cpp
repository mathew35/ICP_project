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
bool GhostObject::isPacman()
{
	return false;
}
int GhostObject::getLives() {
	return 0;
}
bool GhostObject::move(Field::Direction dir) {
	PathField* nextField;
	PathField* prevField;
	switch (dir)
	{
	case Field::L:
		if (this->leftField->canMove())
		{
			nextField = static_cast<PathField*>(this->leftField);
			prevField = this->callerField;
		}
		prevField->fieldObject = nullptr;
		nextField->setGhostObject(this);
		observer->notifyMove(this->row, this->col, this->row, this->col - 1);
		this->col = -1;
		return true;
	case Field::U:
		if (this->upperField->canMove())
		{
			nextField = static_cast<PathField*>(this->upperField);
			prevField = this->callerField;
		}
		prevField->fieldObject = nullptr;
		nextField->setGhostObject(this);
		observer->notifyMove(this->row, this->col, this->row - 1, this->col);
		this->row = -1;
		return true;
	case Field::R:
		if (this->rightField->canMove())
		{
			nextField = static_cast<PathField*>(this->rightField);
			prevField = this->callerField;
		}
		prevField->fieldObject = nullptr;
		nextField->setGhostObject(this);
		observer->notifyMove(this->row, this->col, this->row, this->col + 1);
		this->col = +1;
		return true;
	case Field::D:
		if (this->bottomField->canMove())
		{
			nextField = static_cast<PathField*>(this->bottomField);
			prevField = this->callerField;
		}
		prevField->fieldObject = nullptr;
		nextField->setGhostObject(this);
		observer->notifyMove(this->row, this->col, this->row + 1, this->col);
		this->row = +1;
		return true;
	default:
		return false;
	}
	//TODO decrease lives when meet pacman
}
void GhostObject::attach(GameInterface* o) {
	this->observer = o;
}

void GhostObject::detach(GameInterface* o) {
	if (observer == o)
	{
		this->observer = nullptr;
	}
}
