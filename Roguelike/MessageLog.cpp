#include "MessageLog.h"



MessageLog::MessageLog(Point pos, int width, int height)
	: mPos(pos), mWidth(width), mHeight(height)
{
	AddMessage("C++ is better than Python.", { 255, 255, 0 });
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
		mMessages.push_front(Text(msg, 15, color));
	}

	mMessages.push_front(Text(message, 15, color));

	while (mMessages.size() > mHeight)
		mMessages.pop_back();
}

void MessageLog::Draw()
{
	int y = mHeight - 1;

	std::list<Text>::iterator it;
	for (it = mMessages.begin(); it != mMessages.end(); ++it)
	{
		it->Draw(mPos.tileX, (mPos.tileY + y), true);
		y--;
	}
}