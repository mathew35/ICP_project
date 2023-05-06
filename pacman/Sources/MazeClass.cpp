/**
* @brief
*
* @authors	Adrian Horvath(xhorva14)
*			Matus Vrablik(xvrabl05)
*
*/

#include "MazeClass.h"

#define BOUNDS 2

void MazeClass::horizontalWall(int rows, int cols) {
	for (int c = 0; c < cols; c++)
	{
		this->fieldArray[0][c] = new WallField(0, c);
		this->fieldArray[rows - 1][c] = new WallField(rows - 1, c);
	}
}
void MazeClass::verticalWall(int rows, int cols) {
	for (int r = 1; r < rows - 1; r++)
	{
		this->fieldArray[r][0] = new WallField(r, 0);
		this->fieldArray[r][cols - 1] = new WallField(r, cols - 1);
	}
}
void MazeClass::insertGhost(Field* field) {
	this->listOfGhosts.push_back(field->get());
}

MazeClass::MazeClass(int rows, int cols)
{
	this->createArray(rows + BOUNDS, cols + BOUNDS);
	this->keys = 0;
}

MazeClass::~MazeClass()
{
	//TODO - delete fieldArray?
}

void MazeClass::createArray(int rows, int cols) {
	this->cols = cols;
	this->rows = rows;
	this->fieldArray = new Field * *[rows];

	for (int i = 0; i < rows; ++i) {
		this->fieldArray[i] = new Field * [cols];
		for (int j = 0; j < cols; ++j) {
			this->fieldArray[i][j] = nullptr;
		}
	}
}
void MazeClass::insertLine(std::string line) {
	for (int i = 1; i < this->numCols() - 1; i++)
	{
		switch (line[i - 1])
		{
		case '.':
			this->fieldArray[this->numberOfLines][i] = new PathField(this->numberOfLines, i);
			continue;
		case 'X':
			this->fieldArray[this->numberOfLines][i] = new WallField(this->numberOfLines, i);
			continue;
		case 'S':
			this->fieldArray[this->numberOfLines][i] = new PathField(this->numberOfLines, i, 'S');
			continue;
		case 'G':
			this->fieldArray[this->numberOfLines][i] = new PathField(this->numberOfLines, i, 'G');
			this->insertGhost(this->fieldArray[this->numberOfLines][i]);
			continue;
		case 'T':
			this->fieldArray[this->numberOfLines][i] = new PathField(this->numberOfLines, i, 'T');
			continue;
		case 'K':
			this->fieldArray[this->numberOfLines][i] = new PathField(this->numberOfLines, i, 'K');
			this->keys += 1;
			continue;
		default:
			break;
			//TODO
		}
	}
	this->numberOfLines++;
}
void MazeClass::setFields() {
	for (int r = 1; r < this->numRows() - 1; r++)
	{
		for (int c = 0; c < this->numCols() - 1; c++)
		{
			if (typeid((PathField*)this->fieldArray[r][c]) == typeid(PathField*) && this->fieldArray[r][c] != nullptr) {
				PathField* path = (PathField*)this->fieldArray[r][c];
				path->setSurroundingFields(this->fieldArray[r + 1][c], this->fieldArray[r][c + 1], this->fieldArray[r - 1][c], this->fieldArray[r][c - 1]);
				MazeObject* obj = path->get();
				if (obj != nullptr && typeid(*(DoorObject*)obj) == typeid(DoorObject))
				{
					this->door = (DoorObject*)obj;
					this->door->setKeys(keys);
					continue;
				}
				path->setObjectFields(path->get());
			}
		}
	}
}
DoorObject* MazeClass::getDoor()
{
	return this->door;
}
int MazeClass::getKeys()
{
	return this->keys;
}
int MazeClass::numCols() {
	return this->cols;
}
int MazeClass::numRows() {
	return this->rows;
}

Field* MazeClass::getField(int row, int col) {
	return this->fieldArray[row][col];
}

std::list<MazeObject*> MazeClass::ghosts() {
	std::list<MazeObject*> clonedList;

	for (const auto& obj : listOfGhosts)
	{
		clonedList.push_back(obj);
	}

	return clonedList;

}
