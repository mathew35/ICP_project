/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/
#pragma once

#include <vector>
#include <string>
#include "MazeObject.h"

class MazeConfigure {
public:
	void createArray(int rows, int cols);
	virtual int numCols() override;
	virtual std::vector<MazeObject> ghosts() override;
	virtual int numRows() override;
	virtual Field getField() override;

	void insertLine(std::string line);
	void setFields();
private:
	void insertGhost(Field field);
	void horizontalWall(int rows, int cols);
	void verticalWall(int rows, int cols);
};

