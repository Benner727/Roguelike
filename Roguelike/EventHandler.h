#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "InputHandler.h"

#include "Player.h"
#include "Map.h"

class EventHandler
{
public:
	EventHandler(InputHandler& inputHandler);
	~EventHandler();

private:
	InputHandler& mInputHandler;

public:
	void HandlePlayer(Player& player, Map& map);
};

#endif
