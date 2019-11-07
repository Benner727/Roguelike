#ifndef ENGINE_H
#define ENGINE_H

#include "Audio.h"
#include "InputHandler.h"
#include "Timer.h"

#include "EventHandler.h"
#include "Map.h"
#include "FOV.h"
#include "MessageLog.h"

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
	MessageLog mMessageLog;

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