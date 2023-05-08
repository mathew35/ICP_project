/**
* @brief	ReplayMode implementation
*
* @author	Adrian Horvath(xhorva14)
*
*/
#include "ReplayMode.h"


void ReplayMode::setMazeSize(std::string line)
{
	std::istringstream iss(line);
	iss >> this->rows >> this->cols;
}

void ReplayMode::setMazeFromLog(std::string line)
{
	this->Maze.push_back(line);
}

void ReplayMode::parseLogsFromFile(std::string filePath)
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
		std::string prevLine = line;
		while (std::getline(inputFile, line))
		{
			if (std::regex_match(prevLine, turnRegex) && parsedTurns.empty() && std::regex_match(line, turnRegex))
			{
				parsedTurns.push_back(logList);
				logList.clear();
				continue;
			}
			if (std::regex_match(line, turnRegex))
			{
				parsedTurns.push_back(logList);
				logList.clear();
				continue;
			}
			logList.push_back(line);
		}
		parsedTurns.push_back(logList);
		inputFile.close();
	}
}

ReplayMode::ReplayMode(std::string filePath, mainwindow* window, bool fromStart) : logRegex("(Pacman|Ghost) \\[(\\d+),(\\d+)\\] -> \\[(\\d+),(\\d+)\\]"
	"|Door \\[(\\d+),(\\d+)\\] \\[OPEN\\]"
	"|Key \\[(\\d+),(\\d+)\\] \\[PICKED UP\\]"
	"|Pacman lives \\[(\\d+)\\] -> \\[(\\d+)\\]"), turnRegex("TURN (\\d+)")
{
	parseLogsFromFile(filePath);
	turns = 0;
	if (!fromStart)
	{
		turns = parsedTurns.size() - 1;
	}
	this->window = window;
}

ReplayMode::~ReplayMode()
{
}

std::list<std::string> ReplayMode::getMaze()
{
	return this->Maze;
}

bool ReplayMode::parseLogsFromTurn(bool reverse)
{
	if (this->turns > parsedTurns.size() - 1 || this->turns < 0)
	{
		return false;
	}

	std::list<std::string> logsInTurn = parsedTurns[turns];

	if (reverse)
	{
		for (auto it = logsInTurn.rbegin(); it != logsInTurn.rend(); ++it) {

			const std::string& log = *it;

			std::smatch match;

			if (std::regex_match(log, match, logRegex)) {
				if (match[1].matched) {

					// Pacman or Ghost log
					std::string objectType = match[1].str();
					int x2 = std::stoi(match[2].str());
					int y2 = std::stoi(match[3].str());
					int x1 = std::stoi(match[4].str());
					int y1 = std::stoi(match[5].str());

					// Perform actions based on the log content
					if (objectType == "Pacman") {
						//TODO move pacman
						this->window->replayStep(this->turns);
						this->window->replayPacmanMove(x1, y1, x2, y2);

						// Use the extracted values
						std::cout << "Object Type: " << "Pacman" << std::endl;
						std::cout << "x1: " << x1 << std::endl;
						std::cout << "y1: " << y1 << std::endl;
						std::cout << "x2: " << x2 << std::endl;
						std::cout << "y2: " << y2 << std::endl;

					}
					else if (objectType == "Ghost") {
						//TODO move ghost
						this->window->replayGhostMove(x1, y1, x2, y2);
						// Use the extracted values
						std::cout << "Object Type: " << "Ghost" << std::endl;
						std::cout << "x1: " << x1 << std::endl;
						std::cout << "y1: " << y1 << std::endl;
						std::cout << "x2: " << x2 << std::endl;
						std::cout << "y2: " << y2 << std::endl;

					}
				}
				else if (match[6].matched) {
					// Door log
					int x = std::stoi(match[6].str());
					int y = std::stoi(match[7].str());

					//TODO doors
					this->window->replayDoor(false);
					std::cout << "Door x: " << x << std::endl;
					std::cout << "Door y: " << y << std::endl;
				}
				else if (match[9].matched) {
					// Key log
					int x = std::stoi(match[9].str());
					int y = std::stoi(match[10].str());

					//TODO key
					this->window->replayKey(x, y);
					std::cout << "Key x: " << x << std::endl;
					std::cout << "Key y: " << y << std::endl;
				}
				else if (match[11].matched) {
					// Pacman HP log
					int hp2 = std::stoi(match[11].str());
					int hp1 = std::stoi(match[12].str());

					//TODO pacman hp
					this->window->replayLive(hp1, hp2);
					std::cout << "Pacman HP 1: " << hp1 << std::endl;
					std::cout << "Pacman HP 2: " << hp2 << std::endl;
				}
			}
			else {
				// Invalid log format
				throw _exception();

			}
		}
		this->turns--;
	}
	else
	{
		for (auto it = logsInTurn.begin(); it != logsInTurn.end(); ++it) {

			const std::string& log = *it;

			std::smatch match;

			if (std::regex_match(log, match, logRegex)) {
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
						this->window->replayStep(this->turns);
						this->window->replayPacmanMove(x1, y1, x2, y2);
						// Use the extracted values
						std::cout << "Object Type: " << "Pacman" << std::endl;
						std::cout << "x1: " << x1 << std::endl;
						std::cout << "y1: " << y1 << std::endl;
						std::cout << "x2: " << x2 << std::endl;
						std::cout << "y2: " << y2 << std::endl;

					}
					else if (objectType == "Ghost") {
						//TODO move ghost
						this->window->replayGhostMove(x1, y1, x2, y2);
						// Use the extracted values
						std::cout << "Object Type: " << "Ghost" << std::endl;
						std::cout << "x1: " << x1 << std::endl;
						std::cout << "y1: " << y1 << std::endl;
						std::cout << "x2: " << x2 << std::endl;
						std::cout << "y2: " << y2 << std::endl;

					}
				}
				else if (match[6].matched) {
					// Door log
					int x = std::stoi(match[6].str());
					int y = std::stoi(match[7].str());

					//TODO doors
					this->window->replayDoor(true);
					std::cout << "Door x: " << x << std::endl;
					std::cout << "Door y: " << y << std::endl;
				}
				else if (match[9].matched) {
					// Key log
					int x = std::stoi(match[9].str());
					int y = std::stoi(match[10].str());

					//TODO key
					this->window->replayKey(x, y);
					std::cout << "Key x: " << x << std::endl;
					std::cout << "Key y: " << y << std::endl;
				}
				else if (match[11].matched) {
					// Pacman HP log
					int hp1 = std::stoi(match[11].str());
					int hp2 = std::stoi(match[12].str());

					//TODO pacman hp
					this->window->replayLive(hp1, hp2);
					std::cout << "Pacman HP 1: " << hp1 << std::endl;
					std::cout << "Pacman HP 2: " << hp2 << std::endl;
				}
			}
			else {
				// Invalid log format
				//TODO

				std::cout << "No match found." << std::endl;
			}
		}
		this->turns++;
	}
}

