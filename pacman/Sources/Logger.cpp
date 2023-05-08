/**
* @brief Logger of gameplay for later replay
*
* @author Adrian Horvath(xhorva14)
*
*/
#include "Logger.h"

Logger::Logger()
{
	int num = 0;
	std::string Filename = "Log";
	std::string newFilename = Filename;
	while (std::filesystem::exists(newFilename)) {
		num++;
		//TODO FIX ME CREATE LOG FILE
		newFilename = newFilename + "_" + std::to_string(num);
	}
	this->m_filename = newFilename;
	this->m_logFile.open(m_filename);
	if (m_logFile.fail()) {
		throw new std::exception();
	}
}

Logger::~Logger()
{
	this->m_logFile.close();
}

void Logger::printTurnZero()
{
	this->m_logFile << "TURN: " << this->turn << std::endl;
}

void Logger::printFirstLine(int rows, int cols)
{
	std::string line = std::to_string(rows) + " " + std::to_string(cols);
	this->m_logFile << line << std::endl;
}

void Logger::printMazeLine(std::string line)
{
	this->m_logFile << line << std::endl;
}

void Logger::printMovement(MazeObject* object, int fromX, int fromY, int toX, int toY)
{

	std::string entity;

	PacmanObject* pacman = (PacmanObject*)object;
	GhostObject* ghost = (GhostObject*)object;
	if (object == nullptr) { return; };
	if (typeid(*pacman) == typeid(PacmanObject)) {
		if (turn > 0)
		{
			this->m_logFile << "TURN:" << this->turn << std::endl;
		}
		this->turn++;
		entity = "Pacman ";
	}
	else if (typeid(*ghost) == typeid(GhostObject)) {
		entity = "Ghost ";
	}

	this->m_logFile << entity << "[" << fromX << "," << fromY << "]" << " -> " << "[" << toX << "," << toY << "]" << std::endl;
}

void Logger::printDoor(int x, int y)
{
	this->m_logFile << "Doors [" << x << "," << y << "]" << "[OPEN]" << std::endl;
}

void Logger::printKey(int x, int y)
{
	this->m_logFile << "Key [" << x << "," << y << "]" << "[PICKED UP]" << std::endl;
}

void Logger::printLives(int lives)
{
	int prevLives = lives + 1;
	this->m_logFile << "Pacman lives [" << prevLives << "]" << " -> " << "[" << lives << "]" << std::endl;
}
