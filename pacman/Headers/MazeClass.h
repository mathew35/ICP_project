/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/
#pragma once

#include <list>
#include <string>
#include "MazeObject.h"
#include "Field.h"

class MazeClass : public Maze {
public:
	void createArray(int rows, int cols);
	int numCols() override;
	std::list<MazeObject*> ghosts() override;
	int numRows() override;
	Field* getField(int row, int col) override;

	void insertLine(std::string line);
	void setFields();
private:
	void insertGhost(Field field);
	void horizontalWall(int rows, int cols);
	void verticalWall(int rows, int cols);
};
