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

class ReplayMode {
private:
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
	ReplayMode(std::string filePath, bool fromStart = true);
	~ReplayMode();
	bool parseLogsFromTurn(bool reverse = false);
};

