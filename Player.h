#pragma once
#include "Character.h"
class Player :public Character
{
private:
	int xcoordinate;
	int ycoordinate;
	int goldcount;
	int level;
	int experience;
	int tolevelup;

public:
	double attack();
	void information();
	void drinkpotion();
	void addexperience(int e);
	void levelup();
	void setxcoordinate(int x);
	int getxcoordinate();
	void setycoordinate(int y);
	int getycoordinate();
	void setgoldcount(int gcc);
	int getgoldcount();
	void setlevel(int l);
	int getlevel();
	void setexperience(int ex);
	int getexperience();
	void settolevelup(int tlu);
	int gettolevelup();

	Player();
	Player(char, int, int);
	~Player();
};

