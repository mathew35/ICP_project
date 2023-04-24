/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/

#include "PacmanObject.h"
#include "PathField.cpp"
#include "Field.h"

class PacmanObject : public MazeObject {
private:
	int lives = 3
protected:
	int row;
	int col;
	PathField* callerField;
	Field* bottomField;
	Field* rightField;
	Field* upperField;
	Field* leftField;

public:
	PacmanObject(int row, int col, PathField* Field) {
		this->row = row;
		this->col = col;
		this->callerField = Field;
	}

	void setSurroundinFieldsPacman(Field* bottom, Field* right, Field* upper, Field* left, PathField* curPath) {
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
		return this->lives;
	}
	bool move(Field::Direction dir) {
		//TODO move
		return true;
	}
	bool decreaseLives() {
		if (this->lives == 0)
			return false; //RIP Pacman
		this->lives -= 1;
		return true;
	}
};
