#pragma once

#include "Globals.h"
#include "SDL\include\SDL.h"

#define RAND_MAX 4000
#define RAND_MIN 0

class AusRandom
{
public:

	// Constructor
	AusRandom();
	void Start();
	float RandZeroAndOne();
	void RandMinMax();


private:
	
};