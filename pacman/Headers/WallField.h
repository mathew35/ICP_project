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

class WallField : public Field {
private:
	char fieldType;
	int row;
	int col;
public:
	WallField(int row, int col);

	bool canMove() override;

	bool contains(MazeObject* obj);

	MazeObject* get() override;

	bool isEmpty() override;

	Field* nextField(Field::Direction dir);

	char getType() override;

};
