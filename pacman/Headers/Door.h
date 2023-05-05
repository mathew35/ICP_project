#pragma once

#include "MazeItem.h"
#include "GameInterface.h"
#include "Logger.h"

class Door : public MazeItem {
private:
	bool open;
	Logger* logger;
	GameInterface* observer;
protected:
	int row;
	int col;
	int keys;
public:
	Door(int row, int col, GameInterface* o, Logger* logger, int keys);
	~Door();
	bool isOpen();
	void openDoors();
};