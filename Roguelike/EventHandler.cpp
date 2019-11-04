#include "EventHandler.h"

EventHandler::EventHandler(InputHandler& inputHandler)
	: mInputHandler(inputHandler)
{
}

EventHandler::~EventHandler()
{
}

void EventHandler::HandlePlayer(Player* mPlayer)
{
	if (mInputHandler.KeyDown(mInputHandler.LastKey()))
	{
		switch (mInputHandler.LastKey())
		{
		case SDL_SCANCODE_A:
			mPlayer->MoveLeft();
			break;
		case SDL_SCANCODE_D:
			mPlayer->MoveRight();
			break;
		case SDL_SCANCODE_S:
			mPlayer->MoveDown();
			break;
		case SDL_SCANCODE_W:
			mPlayer->MoveUp();
			break;
		}
	}
}
