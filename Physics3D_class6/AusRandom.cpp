// ----------------------------------------------------
// AusRandom.cpp
// Class to generate random numbers
// ----------------------------------------------------

#include "AusRandom.h"
#include <random>
#include <map>
// ---------------------------------------------
AusRandom::AusRandom()
{

}
void AusRandom::Start()
{
	
	
}
// Returns a float between 0 and 1
float AusRandom::RandZeroAndOne()
{
	float num = 0.0f;
	
	HCRYPTPROV*   hCryptProv = new HCRYPTPROV();
	BYTE         pbData[4];
	if (CryptGenRandom(*hCryptProv, 8, pbData))
	{
		LOG("Random Initalized");
	}

	memcpy(&num, pbData, sizeof(float));



	return num;

}

// Returns and integrer between RAND_MAX and RAND_MIN
void AusRandom::RandMinMax()
{

}



