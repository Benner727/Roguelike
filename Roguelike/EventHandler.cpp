#include "EventHandler.h"

EventHandler::EventHandler(InputHandler& inputHandler)
	: mInputHandler(inputHandler)
{
	mMiniMapSize = 2;
}

EventHandler::~EventHandler()
{
}

void EventHandler::Move(Player& player, Map& map, SDL_Scancode input)
{
	Point newPos(player.GetXPos(), player.GetYPos());

	switch (input)
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
	}

	if (map.Walkable(newPos.tileX, newPos.tileY))
		player.Move(newPos);
}

void EventHandler::HandlePlayer(Player& player, Map& map, MessageLog &messageLog)
{
	if (mInputHandler.KeyDown(mInputHandler.LastKey()))
	{
		Point newPos(player.GetXPos(), player.GetYPos());

		//Opens and closes inventory
		if (mInputHandler.LastKey() == SDL_SCANCODE_I) player.ToggleInventory();

		if (!player.InventoryOpen())
		{
			switch (mInputHandler.LastKey())
			{
			case SDL_SCANCODE_A: //Move left
			case SDL_SCANCODE_D: //Move right
			case SDL_SCANCODE_S: //Move down
			case SDL_SCANCODE_W: //Move up
				Move(player, map, mInputHandler.LastKey());
				break;
			case SDL_SCANCODE_SPACE: //Next level
				if (player.GetXPos() == map.EndPos().tileX &&
					player.GetYPos() == map.EndPos().tileY)
				{
					map.GenerateNewMap();
					player.Move(map.StartPos());
				}
				break;
			case SDL_SCANCODE_Z: //Show chat
				messageLog.ResetDisplayTimer();
				break;
			case SDL_SCANCODE_M: //Resize minimap
				mMiniMapSize++;
				if (mMiniMapSize > MAX_MINIMAP_SIZE)
					mMiniMapSize = 0;
				break;
			}
		}
	}
}

void EventHandler::HandleInventory(Player& player)
{
	bool leftClicked = mInputHandler.MouseButtonPressed(InputHandler::left);
	bool pressed_E = mInputHandler.LastKey() == SDL_SCANCODE_E;

	Inventory& inventory = player.Inventory();

	if (inventory.Open())
	{
		int selected = inventory.Selected();

		if (pressed_E && player.CanEquip(selected))
		{
			player.Equip(selected);
		}

		if (leftClicked)
		{
			inventory.Select(mInputHandler.MousePosX(), mInputHandler.MousePosY());
		}
	}
}