// CMPE 225 GAME				Prepared by:
                                //Burak CANBAZ     150308024
#include <iomanip>              //Onur KARTAL      150308027
#include "stdafx.h"             //Can Ýsmail ÝÇÖZ  150308006
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <time.h>
using namespace std;
#include "Enemy.h"
#include "GameObject.h"
#include "Player.h"
#include "Character.h"
#include "FinishPoint.h"
#include "Gold.h"
int sign1(int num)                  //Bize uzaklýk için positif bir deðer döndürüyor.//
{
	return num < 0 ? num*(-1) : num;
}

bool uzaklýk(Player oyuncu, int i, int j)    //Uzaklýðýn x ve y kordinatlarýný hesaplýyor.//
{
	int xuz, yuz;
	xuz = sign1(oyuncu.getxcoordinate() - i);
	yuz = sign1(oyuncu.getycoordinate() - j);
	return (xuz <= 1 && yuz <= 1);
}
void sis(int &x, int &y, int hareket)
{
	switch (hareket)		// Bu kýsýmda eðer ekranýn en son kýsmýna gelinirse karakteri ayný doðrulta en baþa yada sona atmak için bize deðer üretiyorr//
	{												
	case 1:
		x = (x - 1 + 10) % 10;
		break;
	case 2:
		x = (x + 1 + 10) % 10;
		break;
	case 3:
		y = (y + 1 + 10) % 10;
		break;
	case 4:
		y = (y - 1 + 10) % 10;
		break;
	}
}
void hareket(Player &oyuncu, int hareket)
{
	int x, y;
	x = oyuncu.getxcoordinate();
	y = oyuncu.getycoordinate();					//Bu fonksiyon bir üst fonksiyonda ürettiðimiz deðere göre bizim hareketimizi saðlýyor//
	sis(x, y, hareket);								
	oyuncu.setxcoordinate(x);
	oyuncu.setycoordinate(y);
}


int pvsdsvs(Player *oyuncu, Enemy *enemy)
{
	int  d,a = 0,t;
	int flag = 0;
	double odamage,edamage, ohealth, oarm;
	ohealth = oyuncu->gethealth();									//Bu fonksiyon bizim savaþ dinamiklerimizi içeriyor.Oyuncunun yada düþmanýn canýna
	oarm = oyuncu->getarmor();										//göre dönen bir döngümüz var kullanýcýya seçenek sunuyor ve ona göre gerekli iþlemleri uyguluyor.
	enemy->information();											//Daha sonrasýnda düþmanýn nasýl bir hamle yapacaðýna karar veren fonksiyon çaðýrýlýyor.
	while (oyuncu->gethealth()>0 && enemy->gethealth()>0)			//Bu iþlem iki taraftan birisi ölünceye kadar devam ediyor.Eðer düþman ölürse düþmanýn rondom olarak atanmýþ 
		                                                            //experience deðerini kendi experience miktarýmýza ekliyoruz.Bunun yanýnda pot kazanma þansýmýzý kontrol ediyoruz.
	{
		cout << endl;
		cout << "1 for ATTACK , 2 to DRINK POTION:  ";
		cin >> flag;
		switch (flag)
		{
		case 1:
			odamage = oyuncu->attack();
			enemy->takedamage(odamage);
			if (enemy->gethealth() <= 0)
			{
				enemy->sethealth(0);
			}cout << endl << "You applied: " << odamage << " to the enemy. Enemy's current health: " << enemy->gethealth() << endl;
			
			break;
		
		case 2:
		
			oyuncu->drinkpotion();
			break;
		}
		if (enemy->gethealth() > 0) {
			d = enemy->decideaction();
			if (d == 1) {
				edamage = enemy->enemyatack();
				oyuncu->takedamage(edamage);
				if (oyuncu->getisalive()!=true)
				{
					oyuncu->sethealth(0);
				}
				cout << endl << "Enemy ATTACK applied: " << edamage << " To the player. Player's current health: " << oyuncu->gethealth() << endl;

			}
			else if (d == 2)
			{
				if (enemy->getpotioncount() > 0) {
					enemy->drinkpotion();
				}

				else if (enemy->getpotioncount() <= 0) {
					cout << "Enemy decided to ATACK" << endl;
					edamage = enemy->enemyatack();
					oyuncu->takedamage(edamage);
					cout << endl << "Enemy applied: " << edamage << " To the player. Player's current health: " << oyuncu->gethealth() << endl;

				}
			}
		}
	}
			
	if (enemy->getisalive()==false)
	{
		cout << endl << "Your enemy has perished from this world" << endl;
		oyuncu->setexperience(oyuncu->getexperience() + enemy->getexperienceamount());
		
		t = rand() % 100 + 1;
		if (t <= 30) {
			oyuncu->setpotioncount(oyuncu->getpotioncount() + 1);
			cout << "----YOU EARN 1 POTION---";
		}
		cout << "Player Winnnn you collect experience.";
		oyuncu->levelup();
		oyuncu->setarmor(0);
		return a+1;

	}
	else if (oyuncu->getisalive()==false)
	{
		cout << "You have perished from this world, Game over!!!" << endl;
		return a;
	}

}


int kontrol(Player &oyuncu, int hareket, Character *map[10][10], int &gold) //Haritada boþ alaný,düþmaný,bitiþ noktasýný ve altýný kontrol ediyoruz.Bitiþ noktasý ise yeni harýtada yükleniyor.
{                                                                            //Altýn ise oyuncunun altýn sayýsý artýyor.Düþmansa pvsdsvs fonksiyonunu çaðýrýp düþmanla savaþýyor.
	char choose;
	int x, y,a;
	x = oyuncu.getxcoordinate();
	y = oyuncu.getycoordinate();
	sis(x, y, hareket);
	char sembol;
	sembol = map[x][y]->getsign();
	switch (sembol)
	{
	case 'E':
		while (true)
		{
			cout << "Do you want to fight the enemy?Y/N";
			cin >> choose;
			if (choose == 'Y')
			{
				int dvs; 
				Character *map1 = map[x][y];
				Enemy *enemy = dynamic_cast<Enemy*>(map1);
				dvs = pvsdsvs(&oyuncu, enemy);
				
			
				if (dvs == 1)
				{
					
					
					
					system("pause");
					
					map1->setsign('-');
					a = 1;
					break;
				}
				else if (dvs == 0)
				{
					system("pause");
					
					a = 0;
					break;
				}
				break;

			}
			else if (choose == 'N')
			{
				
				a = 5;

				break;
			}
		}
		return a;
		break;
	case 'G':
	{
		Character *map2 = map[x][y];
		Gold *gold1 = dynamic_cast<Gold*>(map2);
		gold = gold1->getgoldamount();
		oyuncu.setgoldcount(oyuncu.getgoldcount() + gold);
		map[x][y] = new Character('-');
		return 2;
	}
	break;
	case'F':
	{	oyuncu.setlevel(oyuncu.getlevel() + 1);
	cout << "Level up!!!" << endl;
	return 3;
	}
	break;
	default:
		return 1;
		break;
	}
}
void showmap(Character *map[10][10], Player oyuncu)  //File'dan alýnan mapi ekrana yazdýrýyoruz.
{
	int pxcor,pycor;
	pxcor = oyuncu.getxcoordinate();
	pycor = oyuncu.getycoordinate();
	cout << setw(22) << "Level:" << oyuncu.getlevel()<<endl;
	cout << setw(10) << " ";
	for (int i = 0; i < 10; i++)
	{
		cout << "- ";
	}
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << setw(10) << "|";
		for (int j = 0; j < 10; j++)
		{
			if (i == pxcor&&j == pycor)
			{
				cout << oyuncu.getsign() << " ";
			}
			else if (uzaklýk(oyuncu, i, j))
			{
				cout << map[i][j]->getsign()<<" ";
			}
			else
			{
				cout << "#" << " ";
			}
		}
		cout << "|" << endl;
	}
	cout << setw(10) << " ";
	for (int i = 0; i < 10; i++)
	{
		cout << "- ";
	}
	cout << endl;
}






int main()
{
	srand(time(NULL));
	char sign1;
	ifstream fin("map.txt");
	Character *map[10][10];
	Player oyuncu('P', 9, 0);
	oyuncu.setpotioncount(5);
	oyuncu.setlevel(1);
	oyuncu.setisalive(true);
	int potamount, gldcost;
	int girdi = 1, check = 1;
	int gold;
	FinishPoint fp('F', 0, 9);
	oyuncu.setmaxhealth(1000);
	oyuncu.sethealth(1000);
	oyuncu.setarmor(20);
	oyuncu.setexperience(0);
	oyuncu.setdamage(100);
	oyuncu.setgoldcount(2000);
	oyuncu.settolevelup(2000);
	oyuncu.setcritchance(8.5);
	
	
	for (int i = 0; i < 10; i++)
	{                                                      //File'dan haritayý alýyoruz.
		for (int j = 0; j < 10; j++)
		{
			fin >> sign1;
			if (sign1 == 'E') {
				int hlth, crt,pt,exp;
				hlth = 500 + rand() % 500 + 1;
				crt = rand() % 100+1;
				pt = rand() % 3 + 1;
				exp = 300 + rand() % 200 + 1;
				map[i][j] = new Enemy('E', hlth, 20, 50, crt,pt,exp);
			}
			else if (sign1 == 'G') {
				int gldmnt;
				gldmnt = 300 + rand() % 201;
				map[i][j] = new Gold('G', gldmnt);
			}
			else if (sign1 == 'F') {
				map[i][j] = new FinishPoint('F', i, j);


			}
			else if (sign1 == '-') {
				map[i][j] = new Character('-');


			}
		}

	}
	showmap(map, oyuncu);
	cout << endl;
	while (girdi!= 6)
	{
		cout <<endl<<endl<< "Enter 1 to move up, 2 to move down, 3 to move right, 4 to move left, 5 to player's information ,6 to exit: ";
		cin >> girdi;
		if (girdi == 5)
		{
			oyuncu.information();
			continue;
		}
		if (girdi == 6)
		{
			system("CLS");
			cout << "Exited.." << endl;
			system("pause");
			break;
		}
		check = kontrol(oyuncu, girdi, map, gold);
		if (check == 0)
		{
			cout << endl << "YOU DIED!!!" << endl;
			system("pause");
			return(0);
		}
		else if (check == 1 || check == 2)
		{
			hareket(oyuncu, girdi);
			system("CLS");
		}
		showmap(map, oyuncu);
		if (check == 2)
		{
			cout << endl << "Gold collected: " << oyuncu.getgoldcount() << endl;
		}
		if (check == 3)
		{
			system("CLS");
			cout<< "---------------NEW MAP EXECUTED---------------" << endl<< endl << endl << endl << endl;
			oyuncu.setxcoordinate(10 - 1);
			oyuncu.setycoordinate(0);

			showmap(map, oyuncu);
		}
		if (check == 5)
		{
			system("CLS");
			showmap(map, oyuncu);
		}


	}

	fin.close();
	return 0;
}