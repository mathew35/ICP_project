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
	Maze* maze;

public:

	GameInterface();
	~GameInterface();
	void loadMap();
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