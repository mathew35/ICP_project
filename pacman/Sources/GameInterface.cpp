/**
 * @brief Game interface holding all game logic.
 *
 * @author Matúš Vráblik (xvrabl05)
 */

#include "GameInterface.h"

GameInterface::GameInterface(mainwindow* window)
{
	this->logger = new Logger();
	config = new MazeConfigure(this->logger);
	maze = NULL;
	maxLives = -1;
	lives = -1;
	player = tuple(-1, -1);
	this->walls = new list<tuple<int, int>>();
	this->ghosts = new list<tuple<int, int>>();
	this->keys = new list<tuple<int, int>>();
	this->window = window;
}

GameInterface::~GameInterface()
{
	delete this->config;
	this->config = nullptr;
	delete this->logger;
	this->logger = nullptr;
	this->window = nullptr;
	delete[] this->walls;
	this->walls = nullptr;
	delete[] this->ghosts;
	this->ghosts = nullptr;
	delete[] this->keys;
	this->keys = nullptr;
}

void GameInterface::loadMap(std::string file)
{
}

void GameInterface::loadMap()
{
	//TODO - add prompt to select file / function to load from file
	config->startReading(4, 3);
	config->processLine("..G");
	config->processLine(".XT");
	config->processLine(".X.");
	config->processLine(".S.");
	config->stopReading();

	maze = config->createMaze();
	//TODO - add signal that map is created?
	updateVariables();
}

void GameInterface::startGame()
{
	for (MazeObject* ghost : maze->ghosts())
	{
		ghost->start();
	}
}

void GameInterface::endGame()
{
	delete this->logger;
	this->logger = new Logger();
	delete this->config;
	this->config = new MazeConfigure(this->logger);
	delete this->ghosts;
	delete this->walls;
	delete this->keys;
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
	return *this->walls;
}

list<tuple<int, int>> GameInterface::getGhosts()
{
	return *this->ghosts;
}

list<tuple<int, int>> GameInterface::getKeys()
{
	return *this->keys;
}

tuple<int, int> GameInterface::getPlayer()
{
	return this->player;
}

tuple<int, int> GameInterface::getDoor()
{
	return this->door;
}

bool GameInterface::isDoorOpen()
{
	return this->doorOpen;
}

void GameInterface::movePlayer(int d)
{
	//TODO add checks - onliner is DANGEROUS - pacman removed after meeting with ghost
	PacmanObject* player = (PacmanObject*)this->maze->getField(std::get<0>(this->player), std::get<1>(this->player))->get();
	try
	{
		player->move(Field::Direction(d));
	}
	catch (const std::exception&)
	{
		//throw(new exception("player not found"));
	}
}

void GameInterface::notifyMove(int fromX, int fromY, int toX, int toY)
{
	updateVariables();
	this->window->updateMap(tuple(fromX, fromY), tuple(toX, toY));
}

void GameInterface::notifyPickKey(int x, int y)
{
	//TODO
}

void GameInterface::notifyOpenDoors(int x, int y)
{
	this->doorOpen = true;
	this->window->updateMap(tuple(x, y), tuple(x, y));
}

void GameInterface::notifyLives()
{
	Field* field = this->maze->getField(std::get<0>(this->player), std::get<1>(this->player));
	if (field != NULL && field->get() != NULL && field->get()->isPacman())
	{
		this->lives = field->get()->getLives();
	}
	this->window->updateLives();
}

void GameInterface::notifyEndLevel()
{
	//TODO
}

void GameInterface::notifyGameOver()
{
	this->endGame();
	this->window->updateEndGame();
}

void GameInterface::updateVariables()
{
	int walls = this->walls->empty();
	if (!this->ghosts->empty())
	{
		this->ghosts->clear();
		//delete this->ghosts;
		//this->ghosts = new list<tuple<int, int>>();
	}
	if (!this->keys->empty())
	{
		this->keys->clear();
		//delete this->keys;
		//this->keys = new list<tuple<int, int>>();
	}
	for (int x = 0; x < maze->numRows(); x++)
	{
		for (int y = 0; y < maze->numCols(); y++)
		{
			auto field = maze->getField(x, y);
			//walls
			if (walls && (field == nullptr || field->getType() == 'X'))
			{
				this->walls->push_back(tuple(x, y));
				continue;
			}
			if (field == nullptr) { continue; }
			MazeObject* obj = field->get();
			if (obj == nullptr) { continue; }
			GhostObject* ghost = (GhostObject*)obj;
			PacmanObject* player = (PacmanObject*)obj;
			DoorObject* Door = (DoorObject*)obj;
			//ghosts
			if (typeid(*ghost) == typeid(GhostObject))
			{
				field->get()->attach(this);
				field->get()->setLogger(this->logger);
				this->ghosts->push_back(tuple(x, y));
				continue;
			}
			//player
			if (typeid(*player) == typeid(PacmanObject))
			{
				field->get()->attach(this);
				field->get()->setLogger(this->logger);
				this->player = tuple(x, y);
				this->lives = field->get()->getLives();
				if (this->maxLives < 0) { this->maxLives = this->lives; }
				continue;
			}
			//door
			if (typeid(*Door) == typeid(DoorObject))
			{
				field->get()->attach(this);
				field->get()->setLogger(this->logger);
				field->get()->start();
				this->door = tuple(x, y);
				continue;
			}
			//keys
			//if (field != NULL && field->getType() == 'K')
			//{
				//TODO
				//continue;
			//}
		}
	}
	//if (std::get<0>(this->player) < 0 || std::get<1>(player) < 0) { throw(new exception("Player not found")); }

}
