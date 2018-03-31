#pragma once
#include <iomanip>
#include "Character.h"
class Gold :public Character
{
private:
	int goldamount;
public:
	void setgoldamount(int ga);
	int getgoldamount();
	Gold();
	Gold(char, int);
	~Gold();
};

