#pragma once

#include"Character.h"
#include <iomanip>
class FinishPoint :public Character
{
private:
	int xcoordinate;
	int ycoordinate;

public:
	void setxcoordinate(int xc);
	int getxcoordinate();
	void setycoordinate(int yc);
	int getycoordinate();
	FinishPoint();
	FinishPoint(char, int, int);
	~FinishPoint();
};

