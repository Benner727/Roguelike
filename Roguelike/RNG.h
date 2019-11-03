#ifndef RNG_H
#define RNG_H

#include <random>
#include <ctime>

class RNG
{
public:
	RNG(unsigned seed) : mGenerator(seed), mRoll(0, 100)
	{
		mSeed = seed;
	}

	~RNG() {}

private:
	unsigned mSeed;

	std::default_random_engine mGenerator;
	std::uniform_int_distribution<int> mRoll;

public:
	int RandomNumber(int min, int max)
	{
		return rint((float)(max - min) * mRoll(mGenerator) / 100.0f) + min;
	}
};

#endif