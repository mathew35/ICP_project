/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/
#pragma once
#include <stdbool.h>
#include "Field.h"
#include "GameInterface.h"

class MazeObject {
public:

	virtual bool canMove(Field::Direction var1) = 0;

	virtual bool move(Field::Direction var1) = 0;

	virtual Field* getField() = 0;

	virtual bool isPacman() = 0;
	virtual int getLives() = 0;
	bool equals(MazeObject* obj);

	virtual void attach(GameInterface* o) = 0;
	virtual void detach(GameInterface* o) = 0;
};