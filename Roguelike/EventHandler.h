#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "InputHandler.h"

#include "Player.h"

class EventHandler
{
public:
	EventHandler(InputHandler& inputHandler);
	~EventHandler();

private:
	InputHandler& mInputHandler;

public:
	void HandlePlayer(Player* mPlayer);
};

#endif
