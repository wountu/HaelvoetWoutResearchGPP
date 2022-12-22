#include "SDLUtil.h"

SDLUtil::SDLUtil(const char* title, const int width, const int height)
	:m_Exit{}
{
	m_pWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
}

SDLUtil::~SDLUtil()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit;
}

void SDLUtil::Event()
{
	SDL_Event event{};
	SDL_PollEvent(&event);
	
	switch (event.type)
	{
	case SDL_QUIT:
		m_Exit = true;
		break;
	}
}

void SDLUtil::Render() const
{
	SDL_RenderClear(m_pRenderer); 

	SDL_RenderPresent(m_pRenderer);
}
