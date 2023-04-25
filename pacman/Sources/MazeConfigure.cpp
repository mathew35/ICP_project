/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/

#include "MazeConfigure.h"



MazeConfigure::MazeConfigure() {

}
void MazeConfigure::startReading(int rows, int cols) {
	//TODO start reading
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

