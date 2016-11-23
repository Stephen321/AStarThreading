#include <SDL.h>
#include <Layer.h>
#include <Level.h>
#include <Vector2D.h>

using namespace muddygames;

class TileLayer : public Layer
{
public:
	TileLayer(int tileSize, const vector<TileSet> &);
	virtual void Update();
	virtual void Render();
	void SetTileIDs(const vector<vector<int>> &);
	void SetTileSize(int);
	TileSet GetTileSetByID(int);
private:
	int m_numColumns;
	int m_numRows;
	int m_tileSize;
	Vector2D m_position;
	Vector2D m_velocity;
	const vector<TileSet> &m_TileSet;
	vector<vector<int>> m_TileIDs;
};
