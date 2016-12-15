#ifndef WORLDCONSTANTS_H
#define WORLDCONSTANTS_H

#include "LevelData.h"

extern const bool USE_THREADS;
extern bool DISPLAY_LINES;
extern bool DISPLAY_FPS;
namespace WorldConstants
{
	//Astar
	extern const int G_COST;

	//threads
	extern const int WORKER_COUNT;

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
	extern const int LEVEL_ONE_NPC_COUNT;
	extern const int LEVEL_TWO_NPC_COUNT;
	extern const int LEVEL_THREE_NPC_COUNT;
	extern const int MAX_P_TARGET_MOVES;

	//timing
	extern const int TICKS_PER_FRAMES;
	extern const int TICKS_PER_PLAYER_UPDATE;
	extern const int TICKS_PER_NPC_UPDATE;

	//tile
	extern const int TILE_SIZE;
	extern const int HALF_SIZE_PATH_SPLIT_MIN;

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
