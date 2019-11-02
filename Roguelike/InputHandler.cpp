#include "InputHandler.h"

#include "Sprite.h"

InputHandler& InputHandler::Instance()
{
	static InputHandler instance;
	return instance;
}

InputHandler::InputHandler()
{
	mKeyboardState = SDL_GetKeyboardState(&mKeyLength);
	mPrevKeyboardState = new Uint8[mKeyLength];
	memcpy(mPrevKeyboardState, mKeyboardState, mKeyLength);

	mLastKey = SDL_SCANCODE_UNKNOWN;
}

InputHandler::~InputHandler()
{
	delete[] mPrevKeyboardState;
}

bool InputHandler::KeyDown(const SDL_Scancode& scanCode)
{
	return mKeyboardState[scanCode];
}

bool InputHandler::KeyPressed(const SDL_Scancode& scanCode)
{
	return !mPrevKeyboardState[scanCode] && mKeyboardState[scanCode];
}

bool InputHandler::KeyReleased(const SDL_Scancode& scanCode)
{
	return mPrevKeyboardState[scanCode] && !mKeyboardState[scanCode];
}

bool InputHandler::MouseButtonDown(const MOUSE_BUTTON& button)
{
	Uint32 mask = 0;

	switch (button)
	{
	case left:
		mask = SDL_BUTTON_LMASK;
		break;
	case right:
		mask = SDL_BUTTON_RMASK;
		break;
	case middle:
		mask = SDL_BUTTON_MMASK;
		break;
	case back:
		mask = SDL_BUTTON_X1MASK;
		break;
	case forward:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	return (mMouseState & mask);
}

bool InputHandler::MouseButtonPressed(const MOUSE_BUTTON& button)
{
	Uint32 mask = 0;

	switch (button)
	{
	case left:
		mask = SDL_BUTTON_LMASK;
		break;
	case right:
		mask = SDL_BUTTON_RMASK;
		break;
	case middle:
		mask = SDL_BUTTON_MMASK;
		break;
	case back:
		mask = SDL_BUTTON_X1MASK;
		break;
	case forward:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	return !(mPrevMouseState & mask) && (mMouseState & mask);
}

bool InputHandler::MouseButtonReleased(const MOUSE_BUTTON& button)
{
	Uint32 mask = 0;

	switch (button)
	{
	case left:
		mask = SDL_BUTTON_LMASK;
		break;
	case right:
		mask = SDL_BUTTON_RMASK;
		break;
	case middle:
		mask = SDL_BUTTON_MMASK;
		break;
	case back:
		mask = SDL_BUTTON_X1MASK;
		break;
	case forward:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	return (mPrevMouseState & mask) && !(mMouseState & mask);
}

const int& InputHandler::MousePosX()
{
	return mMouseXPos / Sprite::TILE_SIZE;
}

const int& InputHandler::MousePosY()
{
	return mMouseYPos / Sprite::TILE_SIZE;
}

void InputHandler::LastKey(const SDL_Scancode& scanCode)
{
	mLastKey = scanCode;
}

const SDL_Scancode& InputHandler::LastKey()
{
	return mLastKey;
}

void InputHandler::Update()
{
	mMouseState = SDL_GetMouseState(&mMouseXPos, &mMouseYPos);
}

void InputHandler::UpdatePrevInput()
{
	memcpy(mPrevKeyboardState, mKeyboardState, mKeyLength);
	mPrevMouseState = mMouseState;

	mLastKey = SDL_SCANCODE_UNKNOWN;
}