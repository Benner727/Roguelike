#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <memory>
#include <iostream>
#include <string>

class Graphics
{
public:
	static const int SCREEN_WIDTH = 768;
	static const int SCREEN_HEIGHT = 512;
	const char* WINDOW_TITLE = "Roguelike";

private:
	static bool sInitialized;

	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> mWindow;
	std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> mRenderer;

	SDL_Color mDefaultDrawColor;

	SDL_Rect mCamera;

	Graphics();
	~Graphics();

	bool Init();

public:
	static Graphics& Instance();
	static bool Initialized();

	std::shared_ptr<SDL_Texture> LoadTexture(std::string path);
	std::shared_ptr<SDL_Texture> CreateTextTexture(std::weak_ptr<TTF_Font> font, const std::string& text, SDL_Color color);

	void ClearBackBuffer();

	void DrawTexture(std::weak_ptr<SDL_Texture> tex, const SDL_Rect* clip = nullptr, SDL_Rect* rend = nullptr, bool ignoreCamera = false);

	void SetCameraPos(int x, int y);

	void DrawPixel(int x, int y, SDL_Color color);

	void Render();
};

#endif