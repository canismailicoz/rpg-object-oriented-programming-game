#pragma once
#include "Character.h"
#include <iomanip>
class Enemy :public Character
{
private:
	int experienceamount;
	double potionchange;
public:
	void information();
	void drinkpotion();
	int decideaction();
	void setexperiencamount(int exa);
	int getexperienceamount();
	void setpotionchange(double pc);
	double getpotionchange();
	double enemyatack();

	Enemy();
	Enemy(char, int, int, int, double,int,int);
	~Enemy();
};

