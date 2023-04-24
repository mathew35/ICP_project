/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/
#pragma once


#include <typeinfo>
#include "PacmanObject.h"
#include "GhostObject.h"
#include "Field.h"

class PathField : public Field {
public:
	PathField(int row, int col);

	PathField(int row, int col, char typeOfObject);

	void setSurroundingFields(Field* bottom, Field* right, Field* upper, Field* left);

	bool canMove() override;

	bool contains(MazeObject* obj);

	MazeObject* get() override;

	bool isEmpty() override;

	Field* nextField(Field::Direction dirs) override;

	void setPacmanObject(MazeObject* fieldObject);

	void setGhostObject(MazeObject* fieldObject);
};
