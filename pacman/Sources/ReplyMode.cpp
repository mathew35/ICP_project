#include "ReplyMode.h"
#include "ReplyMode.h"
#include "ReplyMode.h"
/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/
#include "ReplyMode.h"


void ReplyMode::setMazeSize(std::string line)
{
	std::istringstream iss(line);
	iss >> this->rows >> this->cols;
}

void ReplyMode::setMazeFromLog(std::string line)
{
	this->Maze.push_back(line);
}

void ReplyMode::parseLogsFromFile(std::string filePath)
{



	std::ifstream inputFile(filePath);;
	if (inputFile.is_open())
	{
		std::string line;
		std::getline(inputFile, line);
		setMazeSize(line);
		std::getline(inputFile, line);
		do
		{
			setMazeFromLog(line);
			std::getline(inputFile, line);
		} while (!(std::regex_match(line, turnRegex)));

		std::list<std::string> logList;

		while (std::getline(inputFile, line))
		{
			if (std::regex_match(line, turnRegex))
			{
				parsedTurns.push_back(logList);
				continue;
			}
			logList.push_back(line);
		}
		inputFile.close();
	}
}

ReplyMode::ReplyMode(std::string filePath) : logRegex("(Pacman|Ghost) \\[(\\d+),(\\d+)\\] -> \\[(\\d+),(\\d+)\\]"
	"|Door \\[(\\d+),(\\d+)\\] \\[OPEN\\]"
	"|Key \\[(\\d+),(\\d+)\\] \\[PICKED UP\\]"
	"|Pacman lives \\[(\\d+)\\] -> \\[(\\d+)\\]"), turnRegex("TURN (\\d+)")
{

	parseLogsFromFile(filePath);
}

ReplyMode::~ReplyMode()
{
}

void ReplyMode::parseLogsFromTrun(int turnNumber)
{

	std::list<std::string> logsInTurn = parsedTurns[turnNumber];


	for (const std::string& log : logsInTurn) {

		std::smatch match;

		if (std::regex_match(log, match, logRegex) {
			if (match[1].matched) {

				// Pacman or Ghost log
				std::string objectType = match[1].str();
					int x1 = std::stoi(match[2].str());
					int y1 = std::stoi(match[3].str());
					int x2 = -1;
					int y2 = -1;

					if (match[4].matched && match[5].matched) {
						x2 = std::stoi(match[4].str());
						y2 = std::stoi(match[5].str());
					}

				// Perform actions based on the log content
				if (objectType == "Pacman") {
					//TODO move pacman
				}
				else if (objectType == "Ghost") {
					//TODO move ghost
				}
			}
			else if (match[6].matched) {
				// Door log
				int x = std::stoi(match[6].str());
				int y = std::stoi(match[7].str());

				//TODO doors
			}
			else if (match[9].matched) {
				// Key log
				int x = std::stoi(match[9].str());
				int y = std::stoi(match[10].str());

				//TODO key
			}
			else if (matcher.group(11) != null) {
				// Pacman HP log
				int hp1 = Integer.parseInt(matcher.group(11));
				int hp2 = Integer.parseInt(matcher.group(12));

				//TODO pacman hp
			}
		}
		else {
			// Invalid log format
			//TODO
		}
	}
}
}
