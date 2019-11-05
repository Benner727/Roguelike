#include "EventHandler.h"


EventHandler& EventHandler::Instance()
{
	static EventHandler instance;
	return instance;
}

EventHandler::EventHandler()
{
}

EventHandler::~EventHandler()
{
}

void EventHandler::MovePlayer(Player& mPlayer, Map& mMap)
{
	if (mInputHandler.KeyDown(mInputHandler.LastKey()))
	{
		mPlayer.Move(mInputHandler.LastKey());
	}
}
