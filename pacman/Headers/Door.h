#pragma once

#include "MazeItem.h"
#include "GameInterface.h"

class Door : public MazeItem {
private:
	bool open;
	GameInterface* observer;
protected:
	int row;
	int col;
public:
	Door(int row, int col, GameInterface* o);
	~Door();
	bool isOpen();
	void openDoors();
};