/**
* @brief
*
* @authors	Adrian Horvath(xhorva14)
*			Matus Vrablik(xvrabl05)
*
*/


#include "PathField.h"


PathField::PathField(int row, int col) {
	this->col = col;
	this->row = row;
	this->fieldType = '.';
	this->typeOfObject = 0;
	this->fieldObject = nullptr;
}//TODO add key and door MazeItem

PathField::PathField(int row, int col, char typeOfObject) {
	this->col = col;
	this->row = row;
	this->fieldType = '.';
	this->typeOfObject = typeOfObject;
	if (typeOfObject == 'S')
	{
		this->fieldObject = new PacmanObject(row, col, this);
	}
	else if (typeOfObject == 'G')
	{
		this->fieldObject = new GhostObject(row, col, this);
	}
}

void PathField::setSurroundingFields(Field* bottom, Field* right, Field* upper, Field* left) {
	this->bottomField = bottom;
	this->rightField = right;
	this->upperField = upper;
	this->leftField = left;
}

void PathField::objectMoved() { this->fieldObject = nullptr; }

bool PathField::canMove() {
	return !(this->fieldType == 'X');
}

bool PathField::contains(MazeObject* obj) {
	if (obj->equals(fieldObject))
	{
		return true;
	}
	else
	{
		return false;
	}
}

MazeObject* PathField::get() { return fieldObject; }

bool PathField::isEmpty() {
	if (this->fieldObject == nullptr)
	{
		return true;
	}
	return false;
}

Field* PathField::nextField(Field::Direction dirs) {
	if (dirs == Field::Direction::D) {
		return this->bottomField;
	}
	else if (dirs == Field::Direction::R) {
		return this->rightField;
	}
	else if (dirs == Field::Direction::U)
		return this->upperField;
	else if (dirs == Field::Direction::L) {
		return this->leftField;
	}
	else {
		return nullptr;
	}
}

void PathField::setPacmanObject(MazeObject* fieldObject) {
	this->fieldObject = fieldObject;
	this->typeOfObject = 'S';
	this->setObjectFields(fieldObject);
	//this->setSurroundingFields(this->bottomField, this->rightField, this->upperField, this->leftField);
}

void PathField::setGhostObject(MazeObject* fieldObject) {
	this->fieldObject = fieldObject;
	this->typeOfObject = 'G';
	this->setObjectFields(fieldObject);
	//this->setSurroundingFields(this->bottomField, this->rightField, this->upperField, this->leftField);
}

void PathField::setObjectFields(MazeObject* object) {

	PacmanObject* pacman = (PacmanObject*)object;
	GhostObject* ghost = (GhostObject*)object;
	if (object == nullptr) { return; };
	if (typeid(*pacman) == typeid(PacmanObject)) {
		pacman->setSurroundinFieldsPacman(this->bottomField, this->rightField, this->upperField, this->leftField, this);
	}
	else if (typeid(*ghost) == typeid(GhostObject)) {
		ghost->setSurroundinFieldsGhost(this->bottomField, this->rightField, this->upperField, this->leftField, this);
	}
}

bool PathField::hasItem()
{
	return !(this->item == nullptr);
}

MazeItem* PathField::getItem()
{
	return this->item;
}

void PathField::setItem(MazeItem* item)
{
	this->item = item;
}

char PathField::getType()
{
	return this->fieldType;
}
