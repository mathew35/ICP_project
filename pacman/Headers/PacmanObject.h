/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/
#pragma once

#include "MazeObject.h"
#include "PathField.h"
#include "Field.h"
class PathField;

class PacmanObject : public MazeObject {
private:
	GameInterface* observer;
	int lives = 3;
protected:
	int row;
	int col;
	PathField* callerField;
	Field* bottomField;
	Field* rightField;
	Field* upperField;
	Field* leftField;

public:
	PacmanObject(int row, int col, PathField* field);

	void setSurroundinFieldsPacman(Field* bottom, Field* right, Field* upper, Field* left, PathField* curPath);

	bool canMove(Field::Direction var1) override;
	Field* getField() override;
	bool isPacman() override;
	int getLives() override;
	bool move(Field::Direction dir) override;

	bool decreaseLives();

	void attach(GameInterface* o) override;
	void detach(GameInterface* o) override;

};