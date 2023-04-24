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

class MazeConfigure {
public:
	void startReading(int rows, int cols);
	bool processLine(std::string line);
	bool stopReading();
	Maze createMaze();
};

