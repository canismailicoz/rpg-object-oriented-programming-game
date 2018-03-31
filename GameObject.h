#pragma once
class GameObject
{
	
public:
	char sign;
	virtual void information();
	void setsign(char a);
	virtual char getsign();
	GameObject();
	GameObject(char);
	~GameObject();
};

