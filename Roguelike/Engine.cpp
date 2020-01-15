#include "Engine.h"

Engine& Engine::Instance()
{
	static Engine instance;
	return instance;
}

Engine::Engine()
	: mGraphics(Graphics::Instance()), mAssetManager(AssetManager::Instance()),
	mAudio(Audio::Instance()), mInputHandler(InputHandler::Instance()), mTimer(Timer::Instance()),
	mMessageLog(Point(1, 25), 80, 7)
{
	mQuit = !mGraphics.Initialized();

	mEventHandler = new EventHandler(mInputHandler);
	mMap = new Map(48 * 2, 32 * 2);
	mPlayer = new Player(mMap->StartPos());
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
	mEventHandler->HandlePlayer(*mPlayer, *mMap, mMessageLog);
	mEventHandler->HandleInventory(*mPlayer);

	FOV::CalculateFOV(*mMap, mPlayer->GetXPos(), mPlayer->GetYPos(), 14);
	mGraphics.SetCameraPos(mPlayer->GetXPos() * Sprite::TILE_SIZE * 1.5f, mPlayer->GetYPos() * Sprite::TILE_SIZE * 1.5f);
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
	mMessageLog.Draw();
	MiniMap::Draw(*mMap, mPlayer->GetXPos(), mPlayer->GetYPos(), mEventHandler->MiniMapSize());

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