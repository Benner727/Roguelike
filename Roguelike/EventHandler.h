#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "InputHandler.h"
#include "Player.h"
#include "Map.h"

class EventHandler
{
public:
	EventHandler();
	~EventHandler();

private:
	InputHandler& mInputHandler = InputHandler::Instance();

public:
	static EventHandler& Instance();
	void MovePlayer(Player& mPlayer, Map& mMap);
};

#endif
