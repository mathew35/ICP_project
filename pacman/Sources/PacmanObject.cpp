/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/

#include "PacmanObject.h"
#include "PathField.cpp"
#include "Field.h"


PacmanObject::PacmanObject(int row, int col, PathField* Field) {
	this->row = row;
	this->col = col;
	this->callerField = Field;
}

void PacmanObject::setSurroundinFieldsPacman(Field* bottom, Field* right, Field* upper, Field* left, PathField* curPath) {
	this->bottomField = bottom;
	this->rightField = right;
	this->leftField = left;
	this->upperField = upper;
	this->callerField = curPath;
}

bool PacmanObject::canMove(Field::Direction dir) {
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
Field* PacmanObject::getField() {
	return this->callerField;
}
int PacmanObject::getLives() {
	return this->lives;
}
bool PacmanObject::move(Field::Direction dir) {
	//TODO move
	return true;
}
bool PacmanObject::decreaseLives() {
	if (this->lives == 0)
		return false; //RIP Pacman
	this->lives -= 1;
	return true;
}
};
