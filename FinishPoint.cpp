#include "stdafx.h"
#include "FinishPoint.h"
#include <iomanip>
void FinishPoint::setxcoordinate(int xc) {
	xcoordinate = xc;
}
int FinishPoint::getxcoordinate() {
	return xcoordinate;
}
void FinishPoint::setycoordinate(int yc) {
	ycoordinate = yc;
}
int FinishPoint::getycoordinate() {
	return ycoordinate;
}


FinishPoint::FinishPoint()
{
	
}

FinishPoint::FinishPoint(char sgh, int x, int y)
{
	sign = sgh;
	xcoordinate = x;
	ycoordinate = y;
}


FinishPoint::~FinishPoint()
{
}
