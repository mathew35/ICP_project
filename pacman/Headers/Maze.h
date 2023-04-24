/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/
#pragma once
#include <list>

#include "Field.h"

class Maze {
public:

	virtual Field* getField(int var1, int var2) = 0;

	virtual int numRows() = 0;

	virtual int numCols() = 0;

	virtual std::list<MazeObject*> ghosts() = 0;
};