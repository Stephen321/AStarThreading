#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include <string>
#include "Debug.h"
#include "AbstractFactory.h"
#include "GameObject.h"

using namespace std;

class GameObjectFactory
{
public:
	bool Register(string, AbstractFactory*);
	GameObject* Create(string);
private:
	map<string, AbstractFactory*> m_factories;
};

#endif

