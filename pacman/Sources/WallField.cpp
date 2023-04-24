/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/

#include "WallField.h"

WallField::WallField(int row, int col) {
	this->row = row;
	this->col = col;
	this->fieldType = 'X';
}

bool WallField::canMove() { return false; }

bool WallField::contains(MazeObject* obj) { return false; }

MazeObject* WallField::get() { return nullptr; }

bool WallField::isEmpty() { return true; }

Field* WallField::nextField(Field::Direction dir) { return nullptr; }

};
