/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/
#pragma once
#include "MazeObject.h"
#include "Maze.h"

class Field {
public:

	virtual bool canMove() = 0;

	virtual MazeObject get() = 0;

	virtual bool isEmpty() = 0;

	virtual Field nextField(Direction var1) = 0;

	virtual bool contains(MazeObject var1) = 0;

};