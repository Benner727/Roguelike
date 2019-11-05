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
		int x = mPlayer.GetXPos();
		int y = mPlayer.GetYPos();

		switch (mInputHandler.LastKey())
		{
			case SDL_SCANCODE_A:
				x -= 1;
				y = y;
				break;
			case SDL_SCANCODE_D:
				x += 1;
				y = y;
				break;
			case SDL_SCANCODE_S:
				x = x;
				y += 1;
				break;
			case SDL_SCANCODE_W:
				x = x;
				y -= 1;
				break;
		}

		if (mMap.Walkable(x, y))
		{
			mPlayer.Move(x, y);
		}
	}
}
