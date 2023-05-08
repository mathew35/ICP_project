/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/
#pragma once
#include <iostream>
#include <list>
#include <string>
#include <regex>
#include <fstream>
#include <sstream>
#include "mainwindow.h"

class mainwindow;

class ReplyMode {
private:
	mainwindow* window;
	int turns;
	std::list<std::string> Maze;
	int rows;
	int cols;
	std::vector<std::list<std::string>> parsedTurns;

	std::regex logRegex;
	std::regex turnRegex;

	void setMazeSize(std::string line);
	void setMazeFromLog(std::string line);
	void parseLogsFromFile(std::string filePath);

public:

	ReplyMode(std::string filePath, mainwindow* window, bool fromStart = true);
	~ReplyMode();
	std::list<std::string> getMaze();
	bool parseLogsFromTurn(bool reverse = false);
};

