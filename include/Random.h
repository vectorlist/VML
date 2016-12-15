
#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <time.h>

static std::default_random_engine rndEngine;
static std::mt19937 rndGenTime(time(NULL));
static std::uniform_real_distribution<float> rndFloat(0.f, 1.0f);
static std::uniform_real_distribution<float> rndFloatPI(0.f, M_PI);
static std::uniform_int_distribution<int>	rndInt(0, 100000);

class Random
{
public:
	Random(unsigned int z = 362436069, unsigned int w = 521288629)
		: mZ(z), mW(w)
	{}

	inline float genFloat()
	{
		unsigned int i = genUint();

		return i * 2.328306e-10f;
	}

	unsigned int genUint()
	{
		mZ = 36969 * (mZ & 65535) + (mZ >> 16);
		mW = 18000 * (mW & 65535) + (mW >> 16);
		return (mZ << 16) + mW;
	}

	//halton sequeence 
	static double haltonSeq(const unsigned int index, const unsigned int base);
	//0 to 1 random
	static float genDistFloat();
	static float genDistFloatPI();
	static int genDistInt();
	
protected:
	unsigned int mZ, mW;
};


#endif //RANDOM_H