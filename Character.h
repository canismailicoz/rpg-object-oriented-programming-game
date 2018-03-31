#pragma once
#include "GameObject.h"
#include <iomanip>
class Character :public GameObject
{
private:
	double health;
	double maxhealth;
	double armor;
	double damage;
	double critchance;
	int potioncount;
	bool isalive;
public:
	void takedamage(double damageamount);

	virtual void drinkpotion();
	void sethealth(double h);
	double gethealth();
	void setmaxhealth(double mh);
	double getmaxhealth();
	void setarmor(double a);
	double getarmor();
	void setdamage(double d);
	double getdamage();
	void setcritchance(double cc);
	double getcritchance();
	void setpotioncount(int p);
	int getpotioncount();
	void setisalive(bool ia);
	bool getisalive();
	Character(char);
	Character();
	~Character();
};

