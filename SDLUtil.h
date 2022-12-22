#pragma once
#include "SDL.h"

class SDLUtil
{
public:
	SDLUtil(const char* title, const int width, const int height);
	~SDLUtil();

	SDLUtil(const SDLUtil& other)			 = delete;
	SDLUtil& operator=(const SDLUtil& other) = delete;
	SDLUtil(SDLUtil&& other)				 = delete;
	SDLUtil& operator=(SDLUtil&& other)		 = delete;

	void Event();
	void Render() const;

	bool Exit() const { return m_Exit; }
private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	bool m_Exit;
};

