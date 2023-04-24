/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/
#pragma once

#include "MazeObject.h"
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
	Field* leftField;
public:
	GhostObject(int row, int col, PathField* field);

	void setSurroundinFieldsGhost(Field* bottom, Field* right, Field* upper, Field* left, PathField* curPath);

	bool canMove(Field::Direction var1) override;
	Field* getField() override;
	int getLives() override;
	bool move(Field::Direction dir) override;

};
