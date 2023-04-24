/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/

#include "GhostObject.h"
#include "PathField.cpp"
#include "Field.h"

class GhostObject : public MazeObject {
protected:
	int row;
	int col;
	PathField* callerField;
	Field* bottomField;
	Field* rightField;
	Field* upperField;
	Field* leftField;

public:
	GhostObject(int row, int col, PathField* Field) {
		this->row = row;
		this->col = col;
		this->callerField = Field;
	}

	void setSurroundinFieldsGhost(Field* bottom, Field* right, Field* upper, Field* left, PathField* curPath) {
		this->bottomField = bottom;
		this->rightField = right;
		this->leftField = left;
		this->upperField = upper;
		this->callerField = curPath;
	}

	bool canMove(Field::Direction dir) override {
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
	Field* getField() {
		return this->callerField;
	}
	int getLives() override {
		return 0;
	}
	bool move(Field::Direction dir) {
		//TODO move
		return true;
	}
};
