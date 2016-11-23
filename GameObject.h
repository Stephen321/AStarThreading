#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>
#include "Debug.h"
#include "GameObjectParameters.h"

using namespace std;

class GameObject
{
public:
	GameObject();
	~GameObject();
	virtual void Initialize(const GameObjectParameters*) = 0; 
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual void CleanUp() = 0;
	int GetX();
	void SetX(int);
	int GetY();
	void SetY(int);
private:
	int m_x;
	int m_y;
};
#endif
