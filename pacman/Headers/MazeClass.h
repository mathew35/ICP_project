/**
* @brief
*
* @authors	Adrian Horvath(xhorva14)
*			Matus Vrablik(xvrabl05)
*
*/
#pragma once

#include <list>
#include <string>
#include "PathField.h"
#include "WallField.h"
#include "PacmanObject.h"
#include "GhostObject.h"
#include "Door.h"
#include "Maze.h"
class Door;

class MazeClass : public Maze {
public:
	MazeClass(int rows, int cols);
	~MazeClass();

	void createArray(int rows, int cols);
	int numCols() override;
	std::list<MazeObject*> ghosts() override;
	int numRows() override;
	Field* getField(int row, int col) override;

	void insertLine(std::string line);
	void setFields();
	Door* getDoor();
	int getKeys();
private:
	int numberOfLines = 1;
	std::list<MazeObject*> listOfGhosts;
	Field*** fieldArray;

	int rows;
	int cols;
	int keys;
	Door* door;

	void insertGhost(Field* field);
	void horizontalWall(int rows, int cols);
	void verticalWall(int rows, int cols);
};
