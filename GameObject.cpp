#include "stdafx.h"
#include "GameObject.h"
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
using namespace std;
void  GameObject::information() {}
void GameObject::setsign(char a) {
	sign = a;
}
char  GameObject::getsign() {
	return sign;
}

GameObject::GameObject()
{
}
GameObject::GameObject(char a)
{
	sign = a;
}

GameObject::~GameObject()
{
}
