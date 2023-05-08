/**
* @brief Ghost object header file
*
* @author Adrian Horvath(xhorva14)
*
*/
#pragma once

#include "MazeObject.h"
#include "PacmanObject.h"
#include "PathField.h"
#include "Logger.h"
#include <chrono>
#include <thread>
#include <iostream>
class PathField;
class GameInterface;
class Logger;

class GhostObject : public MazeObject {
private:
	Logger* logger;
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
	~GhostObject();

	void setSurroundinFieldsGhost(Field* bottom, Field* right, Field* upper, Field* left, PathField* curPath);

	bool canMove(Field::Direction var1) override;
	Field* getField() override;
	bool isPacman() override;
	int getLives() override;
	bool move(Field::Direction dir) override;
	void start() override;

	void setLogger(Logger* logger) override;
	void attach(GameInterface* o) override;
	void detach(GameInterface* o) override;
};
