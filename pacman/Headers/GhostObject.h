/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/
#pragma once

#include "MazeObject.h"
#include "PacmanObject.h"
#include "PathField.h"
class PathField;
class GameInterface;

class GhostObject : public MazeObject {
private:
	GameInterface* observer;
protected:
	int row;
	int col;
	PathField* callerField;
	Field* bottomField;
	Field* rightField;
	Field* upperField;
	Field* leftField;
public:
	GhostObject(int row, int col, PathField* field);

	void setSurroundinFieldsGhost(Field* bottom, Field* right, Field* upper, Field* left, PathField* curPath);

	bool canMove(Field::Direction var1) override;
	Field* getField() override;
	bool isPacman() override;
	int getLives() override;
	bool move(Field::Direction dir) override;

	void attach(GameInterface* o) override;
	void detach(GameInterface* o) override;

};
