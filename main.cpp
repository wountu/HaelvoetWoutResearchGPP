#include "SDL.h"
#include "SDLUtil.h"

int main(int argc, char* argv[])
{
	SDLUtil* pWindow = new SDLUtil("Project", 600, 400);

	while (!pWindow->Exit())
	{
		pWindow->Event();
		//pWindow->Update();
		pWindow->Render();
	}

	delete pWindow;

	return 0;
}