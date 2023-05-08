/**
* @brief Field template
*
* @author Adrian Horvath(xhorva14)
*
*/
#pragma once
class MazeObject;

class Field {
public:
	virtual ~Field() = default;
	enum Direction {
		L,
		U,
		R,
		D
	};

	virtual bool canMove() = 0;

	virtual MazeObject* get() = 0;

	virtual bool isEmpty() = 0;

	virtual Field* nextField(Direction var1) = 0;

	virtual bool contains(MazeObject* var1) = 0;

	virtual char getType() = 0;
};