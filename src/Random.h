
#ifndef RANDOM_H
#define RANDOM_H

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

	//halton sequeence algo
	static double haltonSeq(const unsigned int index, const unsigned int base);
	

	

protected:
	unsigned int mZ, mW;
};


#endif //RANDOM_H