/**
* @brief
*
* @author Adrian Horvath(xhorva14)
*
*/
#pragma once

#include "MazeItem.h"

class KeyItem : public MazeItem {
private:
protected:
	int row;
	int col;
public:
	KeyItem(int row, int col);
	~KeyItem();
};