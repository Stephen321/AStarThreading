#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

#include <string>
#include <map>
#include "GameObject.h"

class AbstractFactory
{
public:
	virtual GameObject* CreateGameObject() const = 0;
	virtual ~AbstractFactory();
};

#endif
