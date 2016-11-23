#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <string>
#include <vector>

#include <Debug.h>
#include <Layer.h>

using namespace std;

struct TileSet
{
	int firstGridID;
	int tileWidth;
	int tileHeight;
	int spacing;
	int margin;
	int width;
	int height;
	int numColumns;
	string name;
};


class Level
{
public:
	Level();
	~Level();
	void Update();
	void Render();
	vector<TileSet>* GetTileSet();
	vector<Layer>* GetLayers();
private:
	vector<TileSet> m_TileSet;
	vector<Layer*> m_Layers;
};
#endif
