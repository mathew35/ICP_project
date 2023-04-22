/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/

#include "GhostObject.h"

class GhostObject : public MazeObject {
protected:
	int row;
	int col;
	PathField callerField;
	Field bottomField;
	Field rightField;
	Field upperField;
	Field leftField;

public:
	GhostObject(int row, int col, PathField Field) {
		this->row = row;
		this->col = col;
		this->callerField = Field;
	}

	void setSurroundinFieldsGhost(Field bottom, Field right, Field upper, Field left, PathField curPath) {
		this->bottomField = bottom;
		this->rightField = right;
		this->leftField = left;
		this->upperField = upper;
		this->callerField = curPath;
	}
};
