#pragma once

#include "MazeObject.h"
#include "GameInterface.h"
#include "Logger.h"
#include "PathField.h"
class PathField;

class DoorObject : public MazeObject {
private:
	bool open;
	Logger* logger;
	GameInterface* observer;
protected:
	int row;
	int col;
	int keys;
	PathField* callerField;
public:
	DoorObject(int row, int col, PathField* field);
	~DoorObject();
	void setKeys(int keys);
	bool isOpen();
	void openDoors();

	bool canMove(Field::Direction dir) override { return false; }
	bool move(Field::Direction dir) override { return false; }
	Field* getField() override;
	bool isPacman() override { return false; }
	int getLives() override { return 0; }
	void start() override;

	void setLogger(Logger* logger) override;
	void attach(GameInterface* o) override;
	void detach(GameInterface* o) override;
};