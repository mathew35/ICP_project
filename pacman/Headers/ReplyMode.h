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

class ReplyMode {
private:
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
	ReplyMode(std::string filePath);
	~ReplyMode();
	void parseLogsFromTrun(int turnNumber);
};

