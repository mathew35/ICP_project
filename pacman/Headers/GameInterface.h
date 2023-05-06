/**
 * @brief Game interface header file.
 *
 * @author Matúš Vráblik (xvrabl05)
 */
#pragma once
#include "MazeConfigure.h"
#include "mainwindow.h"
#include "Logger.h"
#include <tuple>
class MazeConfigure;
class Maze;
class mainwindow;
class Logger;

using namespace std;
class GameInterface
{
protected:
	MazeConfigure* config;
	list<tuple<int, int>>* ghosts;
	list<tuple<int, int>>* walls;
	list<tuple<int, int>>* keys;
	tuple<int, int> door;
	tuple<int, int> player;
	int lives;
	int maxLives;
	Maze* maze;

public:

	GameInterface(mainwindow* window);
	~GameInterface();
	void loadMap();
	void loadMap(std::string file);
	void startGame();
	void endGame();
	int getLives();
	int getMaxLives();
	tuple<int, int> getMapSize();
	list<tuple<int, int>> getWalls();
	list<tuple<int, int>> getGhosts();
	list<tuple<int, int>> getKeys();
	tuple<int, int> getPlayer();
	tuple<int, int> getDoor();
	void movePlayer(int d);

	void notifyMove(int fromX, int fromY, int toX, int toY);
	void notifyPickKey(int x, int y);
	void notifyOpenDoors(int x, int y);
	void notifyLives();
	void notifyEndLevel();
	void notifyGameOver();
private:
	Logger* logger;
	mainwindow* window;
};


/*Pohyby strety ducha a hráča - životy , ďalej keď vezme kľúč a keď pôjde do dverí a ukončí level/hru*/
