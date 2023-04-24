/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/

#include "Field.h"
#include "WallField.h"

class WallField : public Field {
private:
	char fieldType;
	int row;
	int col;
public:
	WallField(int row, int col) {
		this->row = row;
		this->col = col;
		this->fieldType = 'X';
	}

	bool canMove() override { return false; }

	bool contains(MazeObject* obj) override { return false; }

	MazeObject* get() override { return nullptr; }

	bool isEmpty() { return true; }

	Field* nextField(Field::Direction dir) { return nullptr; }

};
