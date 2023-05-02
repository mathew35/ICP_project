/**
 * @brief Game interface header file.
 *
 * @author Matúš Vráblik (xvrabl05)
 */
#pragma once
#include "MazeConfigure.h"
#include "WallField.h"

using namespace std;
class GameInterface
{
protected:
	MazeConfigure config;
	list<tuple<int, int>> ghosts;
	list<tuple<int, int>> walls;
	list<tuple<int, int>> keys;
	tuple<int, int> door;
	tuple<int, int> player;
	int lives;
	Maze* maze;

public:

	GameInterface();
	~GameInterface();
	void loadMap();
	void loadMap(std::string file);
	void startGame();
	int getLives();
	tuple<int, int> getMapSize();
	list<tuple<int, int>> getWalls();
	list<tuple<int, int>> getGhosts();
	list<tuple<int, int>> getKeys();
	tuple<int, int> getPlayer();
	tuple<int, int> getDoor();

private:
};