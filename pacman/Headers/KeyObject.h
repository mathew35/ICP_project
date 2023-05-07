/**
* @brief KeyObject header file.
*
* @author Matus Vrablik(xvrabl05)
*
*/
#pragma once

#include "MazeObject.h"
#include "GameInterface.h"
#include "Logger.h"
#include "PathField.h"
class PathField;

class KeyObject : public MazeObject {
private:
	Logger* logger;
	GameInterface* observer;
protected:
	int row;
	int col;
	PathField* callerField;
public:
	KeyObject(int row, int col, PathField* field);
	~KeyObject();

	bool canMove(Field::Direction dir) override { return false; }
	bool move(Field::Direction dir) override { return false; }
	Field* getField() override;
	bool isPacman() override { return false; }
	int getLives() override { return 0; }
	void start() override {};

	void setLogger(Logger* logger) override;
	void attach(GameInterface* o) override;
	void detach(GameInterface* o) override;
};
