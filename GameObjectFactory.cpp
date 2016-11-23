#include <GameObjectFactory.h>

bool GameObjectFactory::Register(string type, AbstractFactory* factory)
{
	map<string, AbstractFactory*>::iterator it = m_factories.find(type);

	if(it != m_factories.end())
	{
		delete factory;
		return false;
	}

	m_factories[type] = factory;
	return true;
}

GameObject* GameObjectFactory::Create(string type)
{
	map<string, AbstractFactory*>::iterator it = m_factories.find(type);

	if(it == m_factories.end())
	{
		DEBUG_MSG("Cannot find Factory");
		return NULL;
	}

	AbstractFactory* factory = (*(it)).second;
	return factory->CreateGameObject();
}
