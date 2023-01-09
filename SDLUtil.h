#pragma once
#include "SDL.h"
#include "Utils.h"

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
	void Update();
	void RenderBackground() const;
	void Render() const;

	void DrawCircle(Utils::Vector2 centre, float radius) const;
	void DrawRect(Utils::Rect rect) const;
	void DrawLine(Utils::Vector2 point1, Utils::Vector2 point2) const;

	void ChangeColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	Utils::Vector2 GetMousePos() const;
	Utils::Rect GetGrabRect() const;

	bool Exit() const { return m_Exit; }
	Utils::Vector2 GetWindowDimensions() const;
private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	bool m_Exit;
	Utils::Vector2 m_TargetPos;
	Utils::Rect m_GrabRect;
	bool m_Grabbing; //Holding right mouse button to grab agents
	Utils::Vector2 m_StartGrabPos, m_ActiveGrabPos;
	Utils::Vector2 m_WindowDimensions;
};

