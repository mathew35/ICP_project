/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/


#include "PathField.h"

class PathField : public Field {
private:
	int row;
	int col;
	char fieldType;
	Field* bottomField;
	Field* upperField;
	Field* rightField;
	Field* leftField;
	char typeOfObject;
public:
	MazeObject* fieldObject;

	PathField(int row, int col) {
		this->col = col;
		this->row = row;
		this->fieldType = '.';
		this->typeOfObject = 0;
		this->fieldObject = nullptr;
	}

	PathField(int row, int col, char typeOfObject) {
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

	void setSurroundingFields(Field* bottom, Field* right, Field* upper, Field* left) {
		//TODO surroundingfields
	}

	void objectMoved() { this->fieldObject = nullptr; }

	bool canMove() override { return !(this->fieldType == 'X'); }

	bool contains(MazeObject* obj) override {
		if (obj->equals(fieldObject))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	MazeObject* get() override { return fieldObject; }

	bool isEmpty() override {
		if (this->fieldObject == nullptr)
		{
			return true;
		}
		return false;
	}

	Field* nextField(Field::Direction dirs) override {
		if (dirs == D) {
			return this->bottomField;
		}
		else if (dirs == R) {
			return this->rightField;
		}
		else if (dirs == U)
			return this->upperField;
		else if (dirs == L) {
			return this->leftField;
		}
		else {
			return nullptr;
		}
	}

	void setPacmanObject(MazeObject* fieldObject) {
		this->fieldObject = fieldObject;
		this->typeOfObject = 'S';
		this->setSurroundingFields(this->bottomField, this->rightField, this->upperField, this->leftField);
	}

	void setGhostObject(MazeObject* fieldObject) {
		this->fieldObject = fieldObject;
		this->typeOfObject = 'G';
		this->setSurroundingFields(this->bottomField, this->rightField, this->upperField, this->leftField);
	}

	void setObjectFields(MazeObject* object) {

		if (typeid(object) == typeid(PacmanObject)) {
			PacmanObject* pacman = static_cast<PacmanObject*>(object);;
			pacman->setSurroundinFieldsPacman(this->bottomField, this->rightField, this->upperField, this->leftField, this);
		}
		else if (typeid(object) == typeid(GhostObject)) {
			GhostObject* ghost = static_cast<GhostObject*>(object);
			ghost->setSurroundinFieldsGhost(this->bottomField, this->rightField, this->upperField, this->leftField, this);
		}
	}
};
