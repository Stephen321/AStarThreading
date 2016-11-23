#ifndef PLAYER_FACTORY_H
#define PLAYER_FACTORY_H

#include "AbstractFactory.h"
#include "Player.h"

class PlayerFactory : public AbstractFactory
{
	GameObject* CreateGameObject() const;
};
#endif
