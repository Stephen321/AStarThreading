#include "WorldConstants.h"
#include <thread>

bool USE_THREADS = true;
//press f to toggle fps
//press l to toggle lines
//press t to toggle threads
bool DISPLAY_LINES = true;
bool DISPLAY_FPS = true;
namespace WorldConstants
{
	//Astar
	const int G_COST = 10;

	//threads
	const int WORKER_COUNT = std::thread::hardware_concurrency() - 1;

	//colours as hex values
	const int NORMAL_COLOUR_ONE =	0x5A0A9C; //90, 10, 156
	const int NORMAL_COLOUR_TWO =	0xB53C90; //181, 60, 144
	const int WALL_COLOUR		=	0x4C0025;		//0, 0, 0
	const int PLAYER_COLOUR		=	0x98E400;		//152, 228, 255
	const int NPC_COLOUR		=	0xFFBF00;		//255, 191, 0

	//characters
	const int LEVEL_ONE_CHAR_SPAWN_WIDTH	= 8;
	const int LEVEL_TWO_CHAR_SPAWN_WIDTH	= 15;
	const int LEVEL_THREE_CHAR_SPAWN_WIDTH	= 40;
	const int LEVEL_ONE_NPC_COUNT			= 5;
	const int LEVEL_TWO_NPC_COUNT			= 50;
	const int LEVEL_THREE_NPC_COUNT			= 500;
	const int MAX_P_TARGET_MOVES			= 25;

	//timing
	const int TICKS_PER_FRAMES		= 10;
	const int TICKS_PER_PLAYER_UPDATE = 50;
	const int TICKS_PER_NPC_UPDATE = 40; //smaller than player update so its fast enough to catch up

	//tile
	const int TILE_SIZE = 15;
	const int HALF_SIZE_PATH_SPLIT_MIN = 20; //min size of a path we split so we only do half of it (so we can follow player quicker)

	//level length
	const int LEVEL_ONE_LENGTH		= 30;
	const int LEVEL_TWO_LENGTH		= 100;
	const int LEVEL_THREE_LENGTH	= 1000;

	//level walls
	const int MAX_WALL_EDGE_GAP = 5;
	const int MIN_WALL_EDGE_GAP = 2;
	const int MIN_WALL_DISTANCE = 3;
	const int LEVEL_ONE_WALLS	= 3;
	const int LEVEL_TWO_WALLS	= 6;
	const int LEVEL_THREE_WALLS = 18;

	//level touching walls
	const int LEVEL_ONE_TOUCHING_WALLS		= 1;
	const int LEVEL_TWO_TOUCHING_WALLS		= 2;
	const int LEVEL_THREE_TOUCHING_WALLS	= 4;

	const int LEVEL_COUNT = 2; //TODO: 3rd level not working correctly, commented out for now.
	const LevelData levels[LEVEL_COUNT] =
	{
		LevelData(LEVEL_ONE_CHAR_SPAWN_WIDTH  ,   LEVEL_ONE_NPC_COUNT,   LEVEL_ONE_LENGTH   , LEVEL_ONE_WALLS   , LEVEL_ONE_TOUCHING_WALLS),
		LevelData(LEVEL_TWO_CHAR_SPAWN_WIDTH  ,   LEVEL_TWO_NPC_COUNT,   LEVEL_TWO_LENGTH   , LEVEL_TWO_WALLS   , LEVEL_TWO_TOUCHING_WALLS)//,
		//LevelData(LEVEL_THREE_CHAR_SPAWN_WIDTH,   LEVEL_THREE_NPC_COUNT,   LEVEL_THREE_LENGTH , LEVEL_THREE_WALLS , LEVEL_THREE_TOUCHING_WALLS)
	};
}