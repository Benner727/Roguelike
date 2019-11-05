#include "Engine.h"

Engine& Engine::Instance()
{
	static Engine instance;
	return instance;
}

Engine::Engine()
	: mGraphics(Graphics::Instance()), mAssetManager(AssetManager::Instance()),
	mAudio(Audio::Instance()), mInputHandler(InputHandler::Instance()), mTimer(Timer::Instance()),
	mEventHandler(EventHandler::Instance())
{
	mQuit = !mGraphics.Initialized();

	mMap = new Map(48 * 2, 32 * 2);
	mPlayer = new Player();
}

Engine::~Engine()
{
	delete mMap;
	delete mPlayer;
}

void Engine::EarlyUpdate()
{
	mTimer.Update();

	mInputHandler.Update();
}

void Engine::Update()
{
	//Update game here
	mMap->Update();

	mEventHandler.MovePlayer(*mPlayer, *mMap);

	FOV::CalculateFOV(*mMap, mPlayer->GetXPos(), mPlayer->GetYPos(), 12);
	mGraphics.SetCameraPos(mPlayer->GetXPos() * Sprite::TILE_SIZE, mPlayer->GetYPos() * Sprite::TILE_SIZE);
}

void Engine::LateUpdate()
{
	mInputHandler.UpdatePrevInput();
}

void Engine::Render()
{
	mGraphics.ClearBackBuffer();

	//Render game here
	mMap->Draw();
	mPlayer->Draw();

	mGraphics.Render();
}

void Engine::Run()
{
	while (!mQuit)
	{
		EarlyUpdate();

		while (SDL_PollEvent(&mEvent) != 0)
		{
			if (mEvent.type == SDL_QUIT)
				mQuit = true;
			else if (mEvent.type == SDL_KEYDOWN)
				mInputHandler.LastKey(mEvent.key.keysym.scancode);
		}

		Update();
		LateUpdate();
		Render();
	}
}