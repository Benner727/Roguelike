#ifndef MESSAGELOG_H
#define NESSAGELOG_H

#include "Text.h"
#include "MathHelper.h"
#include <list>

class MessageLog
{
public:
	MessageLog(Point mPos, int width, int height);
	~MessageLog();

private:
	Point mPos;
	int mWidth;
	int mHeight;
	std::list<Text> mMessages;

public:
	void AddMessage(std::string message, SDL_Color color = { 255, 255, 255 });

	void Draw();
};

#endif