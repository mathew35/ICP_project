/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/

#include "MazeClass.h"
#include "Field.h"
#include "PathField.h"
#include "WallField.h"

class MazeClass : public Maze {
private:
	int numberOfLines = 1;
	std::list<MazeObject> listOfGhosts;
	Field* fieldArray[][];

	void horizontalWall(int rows, int cols) {
		for (int c = 0; c < cols; c++)
		{
			this->fieldArray[0][c] = new WallField(0, c);
			this->fieldArray[rows - 1][c] = new WallField(rows - 1, c);
		}
	}
	void verticalWall(int rows, int cols) {
		for (int r = 1; r < rows - 1; r++)
		{
			this->fieldArray[r][0] = new WallField(r, 0);
			this->fieldArray[r][col - 1] = new WallField(r, cols - 1);
		}
	}
	void insertGhost(Field field) {
		this->listOfGhosts.push_back(field.get());
	}
public:
	void createArray(int rows, int cols) {
		this->fieldArray = new Field[rows][cols];

	}
	void insertLine(std::string line) {
		for (int i = 1; i < this->numCols - 1; i++)
		{
			if (line[i - 1] == '.')
			{
				this->fieldArray[this->numberOfLines][i] = new PathField(this->numberOfLines, i);
			}
			if (line[i - 1] == 'X')
			{
				this->fieldArray[this->numberOfLines][i] = new WallField(this->numberOfLines, i);
			}
			if (line[i - 1] == 'S')
			{
				this->fieldArray[this->numberOfLines][i] = new PathField(this->numberOfLines, i, 'S');
			}
			if (line[i - 1] == 'G')
			{
				this->fieldArray[this->numberOfLines][i] = new PathField(this->numberOfLines, i, 'G');
			}
		}
		this->numberOfLines++;
	}
	void setFields() {
		for (int r = 1; r < this->numRows() - 1; r++)
		{
			for (int c = 0; c < this->numCols() - 1; c++)
			{
				if (typeid(this->fieldArray[r][c]) == typeid(PathField)) {
					PathField path = static_cast<PathField>(this->fieldArray[r][c]);
					path.setSurroundingFields(this->fieldArray[r + 1][c], this->fieldArray[r][c + 1], this->fieldArray[r - 1][c], this->fieldArray[r][c - 1])
				}
			}
		}
	}
	int numCols() override {
		return sizeof(fieldArray[0] / sizeof(fieldArray[0][0]));
	}


};
