/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/
#pragma once

#include "MazeObject.h"
#include "PathField.h"
#include "Field.h"

class PacmanObject : public MazeObject {
private:
	int lives = 3;
protected:
	int row;
	int col;
	PathField* callerField;
	Field* bottomField;
	Field* rightField;
	Field* upperField;
	Field* leftField;

public:
	PacmanObject(int row, int col, PathField* field);

	void setSurroundinFieldsPacman(Field* bottom, Field* right, Field* upper, Field* left, PathField* curPath);

	bool canMove(Field::Direction var1) override;
	Field* getField() override;
	int getLives() override;
	bool move(Field::Direction dir) override;

	bool decreaseLives();
};