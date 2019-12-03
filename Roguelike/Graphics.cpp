#include "Graphics.h"

bool Graphics::sInitialized = false;

Graphics& Graphics::Instance()
{
	static Graphics instance;
	return instance;
}

bool Graphics::Initialized()
{
	return sInitialized;
}

Graphics::Graphics()
	: mWindow(nullptr, SDL_DestroyWindow), mRenderer(nullptr, SDL_DestroyRenderer)
{
	sInitialized = Init();
}

Graphics::~Graphics()
{
	sInitialized = false;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Graphics::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL Initialization Error: " << SDL_GetError() << std::endl;
		return false;
	}

	mWindow.reset(SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN));

	if (!mWindow)
	{
		std::cout << "Window Creation Error: " << SDL_GetError() << std::endl;
		return false;
	}

	mRenderer.reset(SDL_CreateRenderer(mWindow.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

	if (!mRenderer)
	{
		std::cout << "Renderer Creation Error: " << SDL_GetError() << std::endl;
		return false;
	}

	mDefaultDrawColor = { 0x47, 0x2D, 0x3C, 0xFF };
	SDL_SetRenderDrawColor(mRenderer.get(), mDefaultDrawColor.r, mDefaultDrawColor.g, mDefaultDrawColor.b, mDefaultDrawColor.a);
	SDL_SetRenderDrawBlendMode(mRenderer.get(), SDL_BLENDMODE_BLEND);

	int flags = IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags))
	{
		std::cout << "IMG Initialization Error: " << IMG_GetError() << std::endl;
		return false;
	}

	if (TTF_Init() < 0)
	{
		std::cout << "TTF Initialization Error: " << TTF_GetError() << std::endl;
		return false;
	}

	//SDL_RenderSetLogicalSize(mRenderer.get(), SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
	mCamera = SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

	return true;
}

std::shared_ptr<SDL_Texture> Graphics::LoadTexture(std::string path)
{
	std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface(IMG_Load(path.c_str()), SDL_FreeSurface);

	if (!surface)
	{
		std::cout << "Image Load Error: Path " << path.c_str() << " - Error " << IMG_GetError() << std::endl;
		return std::shared_ptr<SDL_Texture>();
	}

	std::shared_ptr<SDL_Texture> tex(SDL_CreateTextureFromSurface(mRenderer.get(), surface.get()), SDL_DestroyTexture);
	if (!tex)
	{
		std::cout << "Create Texture Error: " << SDL_GetError() << std::endl;
		return std::shared_ptr<SDL_Texture>();
	}

	return tex;
}

std::shared_ptr<SDL_Texture> Graphics::CreateTextTexture(std::weak_ptr<TTF_Font> font, const std::string& text, SDL_Color color)
{
	std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface(TTF_RenderText_Solid(font.lock().get(), text.c_str(), color), SDL_FreeSurface);
	if (!surface)
	{
		std::cout << "Text Render Error: " << TTF_GetError() << std::endl;
		return std::shared_ptr<SDL_Texture>();
	}

	std::shared_ptr<SDL_Texture> tex(SDL_CreateTextureFromSurface(mRenderer.get(), surface.get()), SDL_DestroyTexture);
	if (!tex)
	{
		std::cout << "Text Texture Creation Error: " << SDL_GetError() << std::endl;
		return std::shared_ptr<SDL_Texture>();
	}

	return tex;
}

void Graphics::ClearBackBuffer()
{
	SDL_RenderClear(mRenderer.get());
}

void Graphics::DrawTexture(std::weak_ptr<SDL_Texture> tex, const SDL_Rect* clip, SDL_Rect* rend, bool ignoreCamera)
{
	if (!ignoreCamera)
	{
		if (rend->x < mCamera.x) //Left of camera
			return;
		else if (rend->x > mCamera.x + mCamera.w) //Right of camera
			return;
		else if (rend->y < mCamera.y) //Above camera
			return;
		else if (rend->y > mCamera.y + mCamera.h) //Below camera
			return;

		rend->x -= mCamera.x;
		rend->y -= mCamera.y;
	}

	SDL_RenderCopyEx(mRenderer.get(), tex.lock().get(), clip, rend, 0.0f, nullptr, SDL_FLIP_NONE);
}

void Graphics::SetCameraPos(int x, int y)
{
	mCamera.x = x - mCamera.w * 0.5f;
	mCamera.y = y - mCamera.h * 0.5f;
}

void Graphics::DrawPixel(int x, int y, SDL_Color color)
{
	SDL_SetRenderDrawColor(mRenderer.get(), color.r, color.g, color.b, color.a);
	SDL_RenderDrawPoint(mRenderer.get(), x, y);
	SDL_SetRenderDrawColor(mRenderer.get(), mDefaultDrawColor.r, mDefaultDrawColor.g, mDefaultDrawColor.b, mDefaultDrawColor.a);
}

void Graphics::Render()
{
	SDL_RenderPresent(mRenderer.get());
}