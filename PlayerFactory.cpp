#include <PlayerFactory.h>

GameObject* PlayerFactory::CreateGameObject() const
{
	return new Player();
}
