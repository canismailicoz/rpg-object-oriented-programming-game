#include "stdafx.h"
#include "Gold.h"
#include<time.h>
#include <iomanip>
void Gold::setgoldamount(int ga) {
	goldamount = ga;
}
int Gold::getgoldamount() {
	return goldamount;
}
Gold::Gold(char sg, int num)
{
	setsign(sg);
	setgoldamount(num);
}
Gold::Gold()
{
}


Gold::~Gold()
{
}
