/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/

#include "Field.h"

class WallField : public Field {
private:
	char fieldType;
public:
	WallField(int row, int col) {

	}

	bool canMove() override { return !(this->fieldType == 'X'); }

	bool contains(MazeObject obj) override {
		if (obj.equals(this->get()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
