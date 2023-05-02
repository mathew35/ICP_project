/**
 * @brief Game interface holding all game logic.
 *
 * @author Matúš Vráblik (xvrabl05)
 */

#include "GameInterface.h"

GameInterface::GameInterface()
{
	maze = NULL;
}

GameInterface::~GameInterface()
{
}

void GameInterface::loadMap()
{
	//TODO - add prompt to select file / function to load from file
	config.startReading(4, 3);
	config.processLine("..G");
	config.processLine(".X.");
	config.processLine(".X.");
	config.processLine(".S.");
	config.stopReading();

	maze = config.createMaze();
	//TODO - add signal that map is created?
}

void GameInterface::startGame()
{
}

int GameInterface::getLives()
{
	auto objects = maze->ghosts();
	for (const auto obj : objects)
	{
		if (obj->isPacman())
		{
			return obj->getLives();
		}
	}
	return 0;
}

tuple<int, int> GameInterface::getMapSize()
{
	return tuple<int, int>(maze->numRows(), this->maze->numCols());
}

list<tuple<int, int>> GameInterface::getWalls()
{
	list<tuple<int, int>> walls = {};
	for (int x = 0; x < maze->numRows(); x++)
	{
		for (int y = 0; y < maze->numCols(); y++)
		{
			auto field = maze->getField(x, y);

			if (field == NULL || field->getType() == 'X') {
				walls.push_back(tuple(x, y));
			}
		}
	}
	return walls;
}

list<tuple<int, int>> GameInterface::getGhosts()
{
	list<tuple<int, int>> ghosts = {};
	for (int x = 0; x < maze->numRows(); x++)
	{
		for (int y = 0; y < maze->numCols(); y++)
		{
			auto field = maze->getField(x, y);
			if (field != NULL && field->get() != NULL && !field->get()->isPacman())
			{
				ghosts.push_back(tuple(x, y));
			}
		}
	}
	return ghosts;
}

list<tuple<int, int>> GameInterface::getKeys()
{
	return list<tuple<int, int>>();
}

tuple<int, int> GameInterface::getPlayer()
{
	for (int x = 0; x < maze->numRows(); x++)
	{
		for (int y = 0; y < maze->numCols(); y++)
		{
			auto field = maze->getField(x, y);
			if (field != NULL && field->get() != NULL && field->get()->isPacman())
			{
				return tuple(x, y);
			}
		}
	}
	throw(new exception("Player not found"));
}

tuple<int, int> GameInterface::getDoor()
{
	return tuple<int, int>();
}
