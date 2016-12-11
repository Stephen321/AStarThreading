#ifndef WORLDCONSTANTS_H
#define WORLDCONSTANTS_H

#include "LevelData.h"

namespace WorldConstants
{
	//colours as hex values
	extern const int NORMAL_COLOUR_ONE;
	extern const int NORMAL_COLOUR_TWO;
	extern const int WALL_COLOUR;
	extern const int PLAYER_COLOUR;
	extern const int NPC_COLOUR;

	//characters
	extern const int LEVEL_ONE_CHAR_SPAWN_WIDTH;
	extern const int LEVEL_TWO_CHAR_SPAWN_WIDTH;
	extern const int LEVEL_THREE_CHAR_SPAWN_WIDTH;

	//tile
	extern const int TILE_SIZE;

	//level length
	extern const int LEVEL_ONE_LENGTH;
	extern const int LEVEL_TWO_LENGTH;
	extern const int LEVEL_THREE_LENGTH;

	//level walls
	extern const int MAX_WALL_EDGE_GAP;
	extern const int MIN_WALL_EDGE_GAP;
	extern const int MIN_WALL_DISTANCE;
	extern const int LEVEL_ONE_WALLS;
	extern const int LEVEL_TWO_WALLS;
	extern const int LEVEL_THREE_WALLS;

	//level touching walls
	extern const int LEVEL_ONE_TOUCHING_WALLS;
	extern const int LEVEL_TWO_TOUCHING_WALLS;
	extern const int LEVEL_THREE_TOUCHING_WALLS;

	extern const int LEVEL_COUNT;
	extern const LevelData levels[];
}

#endif 
