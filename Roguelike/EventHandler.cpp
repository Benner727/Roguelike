#include "EventHandler.h"

EventHandler::EventHandler(InputHandler& inputHandler)
	: mInputHandler(inputHandler)
{
	mMiniMapSize = 2;
}

EventHandler::~EventHandler()
{
}

void EventHandler::HandlePlayer(Player& player, Map& map, MessageLog &messageLog)
{
	if (mInputHandler.KeyDown(mInputHandler.LastKey()))
	{
		Point newPos(player.GetXPos(), player.GetYPos());

		switch (mInputHandler.LastKey())
		{
		case SDL_SCANCODE_A:
			newPos.tileX -= 1; //Move left
			break;
		case SDL_SCANCODE_D:
			newPos.tileX += 1; //Move right
			break;
		case SDL_SCANCODE_S:
			newPos.tileY += 1; //Move down
			break;
		case SDL_SCANCODE_W:
			newPos.tileY -= 1; //Move up
			break;
		case SDL_SCANCODE_SPACE:
			if (player.GetXPos() == map.EndPos().tileX &&
				player.GetYPos() == map.EndPos().tileY)
			{
				map.GenerateNewMap();
				player.Move(map.StartPos());
			}
			break;
		case SDL_SCANCODE_Z:
			messageLog.ResetDisplayTimer();
		case SDL_SCANCODE_M:
			mMiniMapSize++;
			if (mMiniMapSize > MAX_MINIMAP_SIZE)
				mMiniMapSize = 0;
			break;
		}
		
		if (map.Walkable(newPos.tileX, newPos.tileY))
			player.Move(newPos);
	}
}
