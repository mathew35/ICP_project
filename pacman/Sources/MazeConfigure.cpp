/**
* @brief
*
* @authors	Adrian Horvath(xhorva14)
*			Matúš Vráblik (xvrabl05)
*
*/

#include "MazeConfigure.h"



void MazeConfigure::startReading(int rows, int cols) {
	newMaze = new MazeClass(rows, cols);
}
bool MazeConfigure::processLine(std::string line) {
	this->counLines++;
	if (this->correctLine)
	{
		if (newMaze->numCols() != line.length() + 2)
		{
			return this->correctLine = false;
		}
		newMaze->insertLine(line);
	}
	return this->correctLine;
}
bool MazeConfigure::stopReading() {
	if (this->counLines != newMaze->numRows() - 2)
	{
		return false;
	}
	newMaze->setFields();
	return this->doneReading = true;
}
Maze* MazeConfigure::createMaze() {
	if (this->doneReading && this->correctLine)
	{
		return this->newMaze;
	}
	else
	{
		return nullptr;
	}
}

