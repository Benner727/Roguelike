#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer
{
private:
	Uint32 mStartTicks;
	Uint32 mEndTicks;

	float mDeltaTime;

	Timer();
	~Timer();

public:
	static Timer& Instance();

	float DeltaTime();

	void Update();
};

#endif