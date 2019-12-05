#include "MessageLog.h"



MessageLog::MessageLog(Point pos, int width, int height)
	: mTimer(Timer::Instance()), mPos(pos), mWidth(width), mHeight(height)
{
	mAlwaysDisplay = false;

	AddMessage("C++ is better than Python.", { 255, 255, 0 });
	AddMessage("C++ is better than Python. 1", { 255, 0, 0 });
	AddMessage("C++ is better than Python. 2", { 0, 255, 0 });
	AddMessage("C++ is better than Python. 3", { 0, 255, 255 });
	AddMessage("C++ is better than Python. 4", { 255, 0, 255 });
	AddMessage("C++ is better than Python. 5");
}


MessageLog::~MessageLog()
{
}

void MessageLog::AddMessage(std::string message, SDL_Color color)
{
	while (message.size() > mWidth)
	{
		std::string msg = message.substr(0, mWidth);
		message = message.substr(mWidth, message.size());
		mMessages.push_front(Message(Text(msg, 15, color), DEFAULT_DISPLAY_TIME));
	}

	mMessages.push_front(Message(Text(message, 15, color), DEFAULT_DISPLAY_TIME));

	while (mMessages.size() > mHeight)
		mMessages.pop_back();
}

void MessageLog::ResetDisplayTimer()
{
	std::list<Message>::iterator it;
	for (it = mMessages.begin(); it != mMessages.end(); ++it)
		it->displayTimer = DEFAULT_DISPLAY_TIME;
}

void MessageLog::Draw()
{
	int y = mHeight - 1;

	if (mAlwaysDisplay)
		ResetDisplayTimer();

	std::list<Message>::iterator it;
	for (it = mMessages.begin(); it != mMessages.end(); ++it)
	{
		if (it->displayTimer > 0.0f)
		{
			int alpha = 255 * y / (mHeight - 1);
			it->text.Alpha(alpha);
			it->text.Draw(mPos.tileX, (mPos.tileY + y), true);
			y--;

			it->displayTimer -= mTimer.DeltaTime();
		}
	}
}