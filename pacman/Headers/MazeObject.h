/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/
#pragma once
#include <stdbool.h>
#include "Field.h"

class MazeObject {
public:


	virtual bool canMove(Field.Direction var1) = 0;

	virtual bool move(Field.Direction var1) = 0;

	virtual Field getField() = 0;

	virtual bool isPacman() {
		return false;
	}

	int getLives() = 0;
};