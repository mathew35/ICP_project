#include "PacmanObject.h"
/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/

#include "PacmanObject.h"

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
bool PacmanObject::isPacman()
{
	return true;
}
int PacmanObject::getLives() {
	return this->lives;
}
bool PacmanObject::move(Field::Direction dir) {
	PathField* nextField;
	PathField* prevField;
	switch (dir)
	{
	case Field::L:
		if (!(this->leftField->canMove()))
		{
			return false;
		}
		nextField = static_cast<PathField*>(this->leftField);
		prevField = this->callerField;
		prevField->fieldObject = nullptr;
		if (!(nextField->isEmpty()))
		{
			this->decreaseLives();
		}
		nextField->setPacmanObject(this);
		observer->notifyMove(this->row, this->col, this->row, this->col - 1);
		this->col = -1;
		return true;
	case Field::U:
		if (!(this->upperField->canMove()))
		{
			return false;
		}
		nextField = static_cast<PathField*>(this->upperField);
		prevField = this->callerField;
		prevField->fieldObject = nullptr;
		if (!(nextField->isEmpty()))
		{
			this->decreaseLives();
		}
		nextField->setPacmanObject(this);
		observer->notifyMove(this->row, this->col, this->row - 1, this->col);
		this->row = -1;
		return true;
	case Field::R:
		if (!(this->rightField->canMove()))
		{
			return false;
		}
		nextField = static_cast<PathField*>(this->rightField);
		prevField = this->callerField;
		prevField->fieldObject = nullptr;
		if (!(nextField->isEmpty()))
		{
			this->decreaseLives();
		}
		nextField->setPacmanObject(this);
		observer->notifyMove(this->row, this->col, this->row, this->col + 1);
		this->col = +1;
		return true;
	case Field::D:
		if (!(this->bottomField->canMove()))
		{
			return false;
		}
		nextField = static_cast<PathField*>(this->bottomField);
		prevField = this->callerField;
		prevField->fieldObject = nullptr;
		if (!(nextField->isEmpty()))
		{
			this->decreaseLives();
		}
		nextField->setPacmanObject(this);
		observer->notifyMove(this->row, this->col, this->row + 1, this->col);
		this->row = +1;
		return true;
	default:
		return false;
	}
	//TODO end game when on doors
	//TODO pick up key
}
bool PacmanObject::decreaseLives() {
	observer->notifyLives();
	//TODO Pacman dead
	if (this->lives == 0) {
		observer->notifyGameOver();
		return false; //RIP Pacman
	}
	this->lives -= 1;
	return true;
}
void PacmanObject::attach(GameInterface* o) {
	this->observer = o;
}

void PacmanObject::detach(GameInterface* o) {
	if (observer == o)
	{
		this->observer = nullptr;
	}
};
