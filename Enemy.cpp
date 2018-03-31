#include "stdafx.h"
#include "Enemy.h"
#include <time.h>
#include <iostream>
#include <iomanip>
using namespace std;

double Enemy::enemyatack() {   //Düþmanýn kritik þansýna karar veriliyor ve hasar döndürülüyor.

	if (getcritchance()>= 4.5 || 7.5<= getcritchance()) {
		return (getdamage()*2);

	}
	else {
		return (getdamage());
	}
}
void Enemy::information() { //Düþmanýn bilgileri ekrana bastýrlýyor.
	cout << "---ENEMY'S INFORMATION----"<<endl;
	cout << "Health:" << gethealth() << endl;
	cout << "Maxhealth:" << getmaxhealth() << endl;
	cout << "Armor:" << getarmor() << endl;
	cout << "Damage:" << getdamage() << endl;
	cout << "Potions:" << getpotioncount() << endl;
	cout << "Enemy's experience:" << getexperienceamount() << endl;



}
void Enemy::drinkpotion() { // Düþmanýn pot içme þansý kontrol ediliyor.Eðer potu yoksa otomotik olarak  saldýrý yapýyor.
	double num3, num4;
	srand(time(NULL));
	num3 = getmaxhealth() - gethealth();
	num4 = rand() % 100 + 1;
	if (num3 >= num4) {
		if (getpotioncount() > 0) {
			sethealth(gethealth() + 500);
			setpotioncount(getpotioncount() - 1);
			if (gethealth() > getmaxhealth()) {
				sethealth(getmaxhealth());
			cout << "Enemy drink potion.Enemy's new health is :" << gethealth() << endl;
			

			}
		}
	}


}
int Enemy::decideaction() { //Düþman bize saldýracakmý yoksa potmu içecek bunun kararý veriliyor.
	srand(time(NULL));
	int num;
	double k;
	num = rand() % 2;
	if (num == 0) {
		int numarams = 1;
		return numarams;
		
	}
	else if (num == 1) {
	
		int numm = 2;
			return numm;
	}


}
void Enemy::setexperiencamount(int exa) {
	experienceamount = exa;
}
int Enemy::getexperienceamount() {
	return experienceamount;
}
void Enemy::setpotionchange(double pc) {
	potionchange = pc;
}
double Enemy::getpotionchange() {
	return potionchange;
}

Enemy::Enemy()
{
}

Enemy::Enemy(char sg, int hlth, int armor, int dmg, double crit,int pt,int exp)
{
	sign = sg;
	sethealth(hlth);  
	setmaxhealth(hlth);
	setarmor(armor);
	setdamage(dmg);
	setcritchance(crit);
	setpotioncount(pt);
	setexperiencamount(exp);



	
}


Enemy::~Enemy()
{
}
