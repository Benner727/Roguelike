#include "MessageLog.h"



MessageLog::MessageLog(Point pos, int width, int height)
	: mPos(pos), mWidth(width), mHeight(height)
{
	AddMessage(Message("This is the first message."));
	AddMessage(Message("This is the second message.", { 255, 55, 55 }));
	AddMessage(Message("This is another message.", { 55, 255, 55 }));
	AddMessage(Message("This is the last message.", { 0, 0, 255 }));
	AddMessage(Message("This is the first message."));
	AddMessage(Message("This is the second message."));
	AddMessage(Message("This is another message."));
	AddMessage(Message("This is the last message.", { 125, 125, 125 }));
}


MessageLog::~MessageLog()
{
}

void MessageLog::AddMessage(Message message)
{
	mMessages.push_front(Text(message.text, 15, message.color));

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