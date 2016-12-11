#include "WorldConstants.h"

namespace WorldConstants
{
	//colours as hex values
	const int NORMAL_COLOUR_ONE = 0xC8C8C8; //200, 200, 200
	const int NORMAL_COLOUR_TWO = 0x4600A0; //70, 0, 160
	const int WALL_COLOUR = 0x000000;		//0, 0, 0
	const int PLAYER_COLOUR = 0x0FFFF;		//0, 255, 255
	const int NPC_COLOUR = 0xFF0000;		//255, 0, 0

	//characters
	const int LEVEL_ONE_CHAR_SPAWN_WIDTH = 8;
	const int LEVEL_TWO_CHAR_SPAWN_WIDTH = 15;
	const int LEVEL_THREE_CHAR_SPAWN_WIDTH = 40;
	const int LEVEL_ONE_NPC_COUNT = 5;
	const int LEVEL_TWO_NPC_COUNT = 50;
	const int LEVEL_THREE_NPC_COUNT = 500;
	const int MAX_P_TARGET_MOVES = 30;

	//timing
	const int TICKS_PER_FRAMES = 10;
	const int TICKS_PER_CHAR_UPDATE = 500;

	//tile
	const int TILE_SIZE = 25;

	//level length
	const int LEVEL_ONE_LENGTH = 30;
	const int LEVEL_TWO_LENGTH = 100;
	const int LEVEL_THREE_LENGTH = 1000;

	//level walls
	const int MAX_WALL_EDGE_GAP = 5;
	const int MIN_WALL_EDGE_GAP = 2;
	const int MIN_WALL_DISTANCE = 4;
	const int LEVEL_ONE_WALLS = 3;
	const int LEVEL_TWO_WALLS = 6;
	const int LEVEL_THREE_WALLS = 18;

	//level touching walls
	const int LEVEL_ONE_TOUCHING_WALLS = 1;
	const int LEVEL_TWO_TOUCHING_WALLS = 2;
	const int LEVEL_THREE_TOUCHING_WALLS = 4;

	const int LEVEL_COUNT = 3;
	const LevelData levels[LEVEL_COUNT] =
	{
		LevelData(LEVEL_ONE_CHAR_SPAWN_WIDTH  ,   LEVEL_ONE_NPC_COUNT,   LEVEL_ONE_LENGTH   , LEVEL_ONE_WALLS   , LEVEL_ONE_TOUCHING_WALLS),
		LevelData(LEVEL_TWO_CHAR_SPAWN_WIDTH  ,   LEVEL_TWO_NPC_COUNT,   LEVEL_TWO_LENGTH   , LEVEL_TWO_WALLS   , LEVEL_TWO_TOUCHING_WALLS),
		LevelData(LEVEL_THREE_CHAR_SPAWN_WIDTH,   LEVEL_THREE_NPC_COUNT,   LEVEL_THREE_LENGTH , LEVEL_THREE_WALLS , LEVEL_THREE_TOUCHING_WALLS)
	};
}