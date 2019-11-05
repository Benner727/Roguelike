#ifndef MESSAGELOG_H
#define NESSAGELOG_H

#include "Text.h"
#include "MathHelper.h"
#include <list>

struct Message {
	std::string text;
	SDL_Color color;

	Message(std::string _text, SDL_Color _color = { 255, 255, 255 })
		: text(_text), color(_color) {}
};

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
	void AddMessage(Message message);

	void Draw();
};

#endif