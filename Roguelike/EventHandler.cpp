#include "EventHandler.h"

EventHandler::EventHandler(InputHandler& inputHandler)
	: mInputHandler(inputHandler)
{
}

EventHandler::~EventHandler()
{
}

void EventHandler::HandlePlayer(Player& player, Map& map)
{
	if (mInputHandler.KeyDown(mInputHandler.LastKey()))
	{
		Point dir;

		switch (mInputHandler.LastKey())
		{
		case SDL_SCANCODE_A:
			dir.tileX -= 1; //Move left
			break;
		case SDL_SCANCODE_D:
			dir.tileX += 1; //Move right
			break;
		case SDL_SCANCODE_S:
			dir.tileY += 1; //Move down
			break;
		case SDL_SCANCODE_W:
			dir.tileY -= 1; //Move up
			break;
		}
		
		if (map.Walkable(player.GetXPos() + dir.tileX, player.GetYPos() + dir.tileY))
			player.Move(dir);
	}
}
