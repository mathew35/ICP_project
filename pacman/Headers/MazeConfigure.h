/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/
#pragma once

#include <list>
#include <string>
#include "MazeObject.h"
#include "Maze.h"
#include "MazeClass.h"

class MazeConfigure {
public:
	MazeConfigure();
	void startReading(int rows, int cols);
	bool processLine(std::string line);
	bool stopReading();
	Maze* createMaze();
protected:
	MazeClass* newMaze;
	bool correctLine = true;
	bool doneReading = false;
private:
	int counLines = 0;

};

