#include <Level.h>

Level::Level()
{
}

Level::~Level()
{
}

vector<TileSet>* Level::GetTileSet()
{
	return (&(m_TileSet));
}

void Level::Render()
{
	for(unsigned int i = 0; i < m_Layers.size(); i++)
	{
		m_Layers[i]->Render();
	}
}

void Level::Update()
{
	for(unsigned int i = 0; i < m_Layers.size(); i++)
	{
		m_Layers[i]->Update();
	}
}
