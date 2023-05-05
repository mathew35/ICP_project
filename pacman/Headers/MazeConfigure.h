/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/
#pragma once

#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include "MazeClass.h"
#include "Logger.h"
class MazeClass;
class Maze;

class MazeConfigure {
public:
	MazeConfigure(Logger* logger);
	void loadMapFromFile(std::string file);
	void startReading(int rows, int cols);
	bool processLine(std::string line);
	bool stopReading();
	Maze* createMaze();
protected:
	MazeClass* newMaze;
	bool correctLine = true;
	bool doneReading = false;
private:
	Logger* logger;
	int counLines = 0;

};

