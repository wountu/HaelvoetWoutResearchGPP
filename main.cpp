#include "SDLUtil.h"
#include "Project.h"
#include <chrono>

int main(int argc, char* argv[])
{
	srand(static_cast<unsigned int>(time(nullptr)));
	
	std::cout << "Press LMB to set target to move to\n";
	std::cout << "Hold RMB and drag to select agents\n";
	std::cout << "Press MMB to create an obstacle\n";
	std::cout << "Press F1 to render gird\n";
	std::cout << "Press F2 to alter formation\n";

	SDLUtil* pWindow = new SDLUtil("Project", 600, 400);
	Project* pProject = new Project{pWindow};
	float elapsedSec{};

	while (!pWindow->Exit())
	{
		auto startTime{ std::chrono::steady_clock::now() };

		//Event handling
		pWindow->Event();

		//Update handling
		pWindow->Update();
		pProject->Update(elapsedSec, pWindow->GetMousePos(), pWindow->GetGrabRect());

		//Render handling
		pWindow->RenderBackground();
		pProject->Render();
		pWindow->Render();

		auto endTime{ std::chrono::steady_clock::now() };
		std::chrono::duration<float> deltaSeconds = endTime - startTime;
		elapsedSec = deltaSeconds.count();
	}

	delete pWindow;

	return 0;
}