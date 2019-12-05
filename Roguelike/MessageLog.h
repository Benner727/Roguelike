#ifndef MESSAGELOG_H
#define NESSAGELOG_H

#include "Text.h"
#include "MathHelper.h"
#include "Timer.h"
#include <list>

class MessageLog
{
public:
	MessageLog(Point mPos, int width, int height);
	~MessageLog();

private:
	static const int DEFAULT_DISPLAY_TIME = 10;

	Timer &mTimer;

	Point mPos;
	int mWidth;
	int mHeight;

	bool mAlwaysDisplay;

	struct Message {
		Text text;
		float displayTimer;

		Message(Text _text, float _displayTimer)
			: text(_text), displayTimer(_displayTimer)
		{}
	};

	std::list<Message> mMessages;

public:
	void AddMessage(std::string message, SDL_Color color = { 255, 255, 255 });

	void ResetDisplayTimer();

	void SetAlwaysDisplay(bool alwaysDisplay) { mAlwaysDisplay = alwaysDisplay; }

	void Draw();
};

#endif