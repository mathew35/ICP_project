/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/

#include "MazeConfigure.h"

class MazeConfigure {
private:
	int counLines = 0;
protected:
	MazeClass newMaze;
	bool correctLine = true;
	bool doneReading = false;
public:
	MazeConfigure() {

	}
	void startReading(int rows, int cols) {
	}
	bool processLine(std::string line) {
		this->counLines++;
		if (this->correctLine)
		{

		}
	}
};
