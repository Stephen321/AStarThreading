#include <iostream>
//Define DEBUG
#define DEBUG

//MACRO for streaming DEBUG
#ifdef DEBUG
	#define DEBUG_MSG(x) (std::cout << (x) << std::endl)
#else
	#define DEBUG_MSG(x)
#endif
