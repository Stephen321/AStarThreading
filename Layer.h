#ifndef LAYER_H
#define LAYER_H

#include <iostream>
#include <vector>
#include <Debug.h>

using namespace std;

class Layer
{
public:
	Layer(){}
	virtual ~Layer(){}
	virtual void Render() = 0;
	virtual void Update() = 0;
};
#endif
