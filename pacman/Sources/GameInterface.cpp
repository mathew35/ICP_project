/**
 * @brief Game interface holding all game logic.
 *
 * @author Matúš Vráblik (xvrabl05)
 */

#include "GameInterface.h"

GameInterface::GameInterface(mainwindow* window)
{
	config = new MazeConfigure();
	maze = NULL;
	maxLives = -1;
	lives = -1;
}

GameInterface::~GameInterface()
{
}

void GameInterface::loadMap(std::string file)
{
	config->loadMapFromFile(file);
	maze = config->createMaze();
	//TODO - add signal that map is created?


	list<tuple<int, int>> walls = {};
	list<tuple<int, int>> ghosts = {};
	tuple<int, int> player = tuple(-1, -1);
	int lives = 0;
	for (int x = 0; x < maze->numRows(); x++)
	{
		for (int y = 0; y < maze->numCols(); y++)
		{
			auto field = maze->getField(x, y);
			//walls
			if (field == NULL || field->getType() == 'X')
			{
				walls.push_back(tuple(x, y));
			}
			//ghosts
			if (field != NULL && field->get() != NULL && !field->get()->isPacman())
			{
				ghosts.push_back(tuple(x, y));
			}
			//player
			if (field != NULL && field->get() != NULL && field->get()->isPacman())
			{
				player = tuple(x, y);
				lives = field->get()->getLives();
			}
			//door
			//TODO
			//keys
			//TODO
		}
	}

	this->walls = walls;
	this->ghosts = ghosts;
	if (std::get<0>(player) < 0 || std::get<1>(player) < 0) { throw(new exception("Player not found")); }
	this->player = player;
	this->lives = lives;
	if (this->maxLives == -1) { this->maxLives = lives; }
}

void GameInterface::loadMap()
{
	//TODO - add prompt to select file / function to load from file
	config->startReading(4, 3);
	config->processLine("..G");
	config->processLine(".X.");
	config->processLine(".X.");
	config->processLine(".S.");
	config->stopReading();

	maze = config->createMaze();
	//TODO - add signal that map is created?


	list<tuple<int, int>> walls = {};
	list<tuple<int, int>> ghosts = {};
	tuple<int, int> player = tuple(-1, -1);
	int lives = 0;
	for (int x = 0; x < maze->numRows(); x++)
	{
		for (int y = 0; y < maze->numCols(); y++)
		{
			auto field = maze->getField(x, y);
			//walls
			if (field == NULL || field->getType() == 'X')
			{
				walls.push_back(tuple(x, y));
			}
			//ghosts
			if (field != NULL && field->get() != NULL && !field->get()->isPacman())
			{
				field->get()->attach(this);
				ghosts.push_back(tuple(x, y));
			}
			//player
			if (field != NULL && field->get() != NULL && field->get()->isPacman())
			{
				field->get()->attach(this);
				player = tuple(x, y);
				lives = field->get()->getLives();
			}
			//door
			//TODO
			//keys
			//TODO
		}
	}

	this->walls = walls;
	this->ghosts = ghosts;
	if (std::get<0>(player) < 0 || std::get<1>(player) < 0) { throw(new exception("Player not found")); }
	this->player = player;
	this->lives = lives;
}

void GameInterface::startGame()
{
}

int GameInterface::getLives()
{
	return this->lives;
}

int GameInterface::getMaxLives()
{
	return this->maxLives;
}

tuple<int, int> GameInterface::getMapSize()
{
	return tuple<int, int>(maze->numRows(), this->maze->numCols());
}

list<tuple<int, int>> GameInterface::getWalls()
{
	return this->walls;
}

list<tuple<int, int>> GameInterface::getGhosts()
{
	return this->ghosts;
}

list<tuple<int, int>> GameInterface::getKeys()
{
	return this->keys;
}

tuple<int, int> GameInterface::getPlayer()
{
	return this->player;
}

tuple<int, int> GameInterface::getDoor()
{
	return this->door;
}

void GameInterface::notifyMove(int fromX, int fromY, int toX, int toY)
{
	//TODO
}

void GameInterface::notifyPickKey(int x, int y)
{
	//TODO
}

void GameInterface::notifyOpenDoors(int x, int y)
{
	//TODO
}

void GameInterface::notifyLives()
{
	//TODO
}

void GameInterface::notifyEndLevel()
{
	//TODO
}

void GameInterface::notifyGameOver()
{
	//TODO
}
