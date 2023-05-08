#include "ReplyMode.h"
/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/
#include "ReplyMode.h"


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
		//Parse logs
	}
}
