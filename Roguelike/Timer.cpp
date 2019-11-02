#include "Timer.h"

Timer& Timer::Instance()
{
	static Timer instance;
	return instance;
}

Timer::Timer()
{
	mStartTicks = 0;
	mEndTicks = 0;
	mDeltaTime = 0.0f;
}

Timer::~Timer()
{

}

float Timer::DeltaTime()
{
	return mDeltaTime / 1000.0f;
}

void Timer::Update()
{
	mStartTicks = SDL_GetTicks();
	mDeltaTime = SDL_GetTicks() - mEndTicks;
	mEndTicks = mStartTicks;
}