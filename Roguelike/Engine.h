#ifndef ENGINE_H
#define ENGINE_H

#include "Audio.h"
#include "InputHandler.h"
#include "Timer.h"

#include "EventHandler.h"
#include "Map.h"
#include "Player.h"

class Engine
{
private:
	bool mQuit;

	Graphics& mGraphics;
	AssetManager& mAssetManager;
	Audio& mAudio;
	InputHandler& mInputHandler;

	Timer& mTimer;

	SDL_Event mEvent;
	EventHandler* mEventHandler;

	Player* mPlayer;
	Map* mMap;
	const Uint8* state;

	Engine();
	~Engine();

	void EarlyUpdate();
	void Update();
	void LateUpdate();

	void Render();

public:
	static Engine& Instance();

	void Run();
};

#endif