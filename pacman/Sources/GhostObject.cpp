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
	PathField* nextField = nullptr;
	PathField* prevField = nullptr;
	switch (dir)
	{
	case Field::L:
		if (this->leftField == NULL || !this->leftField->canMove()) { return false; }
		nextField = static_cast<PathField*>(this->leftField);
		prevField = this->callerField;
		if (!prevField->fieldObjectList->empty()) { prevField->fieldObjectList->pop_back(); }
		if (!(nextField->isEmpty()))
		{
			MazeObject* object = nextField->get();
			if (object->isPacman())
			{
				PacmanObject* pacman = static_cast<PacmanObject*>(object);
				pacman->decreaseLives();
			}
		}
		//TODO 2 ghost same field
		nextField->setGhostObject(this);
		this->col -= 1;
		observer->notifyMove(this->row, this->col - 1, this->row, this->col);
		logger->printMovement(this, this->row, this->col - 1, this->row, this->col);
		return true;
	case Field::U:
		if (this->upperField == NULL || !this->upperField->canMove()) { return false; }
		nextField = static_cast<PathField*>(this->upperField);
		prevField = this->callerField;
		if (!prevField->fieldObjectList->empty()) { prevField->fieldObjectList->pop_back(); }
		if (!(nextField->isEmpty()))
		{
			MazeObject* object = nextField->get();
			if (object->isPacman())
			{
				PacmanObject* pacman = static_cast<PacmanObject*>(object);
				pacman->decreaseLives();
			}
		}
		nextField->setGhostObject(this);
		this->row -= 1;
		observer->notifyMove(this->row, this->col, this->row - 1, this->col);
		logger->printMovement(this, this->row, this->col, this->row - 1, this->col);
		return true;
	case Field::R:
		if (this->rightField == NULL || !this->rightField->canMove()) { return false; }
		nextField = static_cast<PathField*>(this->rightField);
		prevField = this->callerField;
		if (!prevField->fieldObjectList->empty()) { prevField->fieldObjectList->pop_back(); }
		if (!(nextField->isEmpty()))
		{
			MazeObject* object = nextField->get();
			if (object->isPacman())
			{
				PacmanObject* pacman = static_cast<PacmanObject*>(object);
				pacman->decreaseLives();
			}
		}
		nextField->setGhostObject(this);
		this->col += 1;
		observer->notifyMove(this->row, this->col, this->row, this->col + 1);
		logger->printMovement(this, this->row, this->col, this->row, this->col + 1);
		return true;
	case Field::D:
		if (this->bottomField == nullptr || !this->bottomField->canMove()) { return false; }
		nextField = static_cast<PathField*>(this->bottomField);
		prevField = this->callerField;
		if (!prevField->fieldObjectList->empty()) { prevField->fieldObjectList->pop_back(); }
		if (!(nextField->isEmpty()))
		{
			MazeObject* object = nextField->get();
			if (object->isPacman())
			{
				PacmanObject* pacman = static_cast<PacmanObject*>(object);
				pacman->decreaseLives();
			}
		}
		nextField->setGhostObject(this);
		this->row += 1;
		observer->notifyMove(this->row, this->col, this->row + 1, this->col);
		logger->printMovement(this, this->row, this->col, this->row + 1, this->col);
		return true;
	default:
		return false;
	}
}
void GhostObject::start()
{
	list<Field::Direction> moveTo;
	list<Field::Direction> dirs = { Field::Direction::D, Field::Direction::R, Field::Direction::U, Field::Direction::L };
	list<Field::Direction>::iterator it;
	moveTo.clear();
	for (Field::Direction d : dirs)
	{
		if (this->canMove(d)) {
			moveTo.push_back(d);
		}
	}

	int randomPos = std::rand() % (moveTo.size() + 1);
	if (randomPos == moveTo.size())
	{
		return;
	}
	int oldRow = this->row;
	int oldCol = this->col;
	it = std::next(moveTo.begin(), randomPos);
	this->move(*it);
	int newRow = this->row;
	int newCol = this->col;
	this->observer->notifyMove(oldRow, oldCol, newRow, newCol);
}

void GhostObject::setLogger(Logger* logger)
{
	this->logger = logger;
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
