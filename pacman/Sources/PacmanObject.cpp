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
	if (this->bottomField != nullptr && dir == Field::D && this->bottomField->canMove())
	{
		return true;
	}
	else if (this->rightField != nullptr && dir == Field::R && this->rightField->canMove())
	{
		return true;
	}
	else if (this->upperField != nullptr && dir == Field::U && this->upperField->canMove())
	{
		return true;
	}
	else if (this->leftField != nullptr && dir == Field::L && this->leftField->canMove())
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
void PacmanObject::start()
{
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
		logger->printMovement(this, this->row, this->col, this->row, this->col - 1);
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
		logger->printMovement(this, this->row, this->col, this->row - 1, this->col);
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
		logger->printMovement(this, this->row, this->col, this->row, this->col + 1);
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
		logger->printMovement(this, this->row, this->col, this->row + 1, this->col);
		this->row = +1;
		return true;
	default:
		return false;
	}
	//TODO end game when on doors
	//TODO pick up key notify + log
}
bool PacmanObject::decreaseLives() {
	//TODO Pacman dead
	this->lives -= 1;
	if (this->lives == 0) {
		observer->notifyGameOver();
		return false; //RIP Pacman
	}
	observer->notifyLives();
	logger->printLives(lives);
	return true;
}
void PacmanObject::setLogger(Logger* logger)
{
	this->logger = logger;
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
