/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/
#pragma once

#include "MazeObject.h"
#include "PathField"
#include "Field.h"

class GhostObject : public MazeObject {
public:
	GhostObject(int row, int col, PathField field);

	void setSurroundinFieldsGhost(Field bottom, Field right, Field upper, Field left, PathField curPath);

	virtual bool canMove(Field::Direction dir) override;
	virtual Field getField() override;
	virtual int getLives() override;
	virtual bool move(Field::Direction dir) override;

};
