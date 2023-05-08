/**
* @brief Logger header file
*
* @author Adrian Horvath(xhorva14)
*
*/
#pragma once
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "MazeObject.h"
#include "PacmanObject.h"
#include "GhostObject.h"

class Logger {
private:
	std::string m_filename;
	std::ofstream m_logFile;
	int turn = 0;
protected:
public:
	Logger();
	~Logger();
	void printTurnZero();
	void printFirstLine(int rows, int cols);
	void printMazeLine(std::string line);
	void printMovement(MazeObject* obj, int fromX, int fromY, int toX, int toY);
	void printDoor(int x, int y);
	void printKey(int x, int y);
	void printLives(int lives);
};

