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
#include "GameInterface.h"
#include "Logger.h"
#include "KeyObject.h"
class PathField;
class GameInterface;
class Logger;
class KeyObject;

class PacmanObject : public MazeObject {
private:
	GameInterface* observer;
	Logger* logger;
	int lives = 3;
	std::list<KeyObject*> keys;
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
	~PacmanObject();

	void setSurroundinFieldsPacman(Field* bottom, Field* right, Field* upper, Field* left, PathField* curPath);

	bool canMove(Field::Direction var1) override;
	Field* getField() override;
	bool isPacman() override;
	int getLives() override;
	void start() override;
	bool move(Field::Direction dir) override;

	bool decreaseLives();

	void setLogger(Logger* logger) override;
	void attach(GameInterface* o) override;
	void detach(GameInterface* o) override;

};