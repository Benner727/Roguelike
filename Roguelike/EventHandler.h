#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "InputHandler.h"
#include "Player.h"
#include "Map.h"
#include "MessageLog.h"

class EventHandler
{
public:
	EventHandler(InputHandler& inputHandler);
	~EventHandler();

private:
	static const int MAX_MINIMAP_SIZE = 3;

	InputHandler& mInputHandler;

	int mMiniMapSize;

	void Move(Player& player, Map& map, SDL_Scancode input);

public:
	int MiniMapSize() { return mMiniMapSize; }

	void HandlePlayer(Player& player, Map& map, MessageLog &messageLog);
};

#endif
