#include "SDL.h"

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* pWindow{ SDL_CreateWindow("Research", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN) };
	SDL_Renderer* pRenderer{ SDL_CreateRenderer(pWindow, -1, 0) };

	return 0;
}