#ifndef LEVEL_PARSER_H
#define LEVEL_PARSER_H
#include "Level.h"
#include "TinyXML2.h"

using namespace tinyxml2;

class LevelParser
{
public:
	Level* ParseLevel(const char* file);
private:
};
#endif
