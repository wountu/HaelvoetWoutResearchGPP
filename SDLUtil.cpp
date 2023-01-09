#include "SDLUtil.h"

SDLUtil::SDLUtil(const char* title, const int width, const int height)
	:m_Exit{}
	,m_TargetPos{}
	,m_GrabRect{}
	,m_Grabbing{}
	,m_StartGrabPos{}
	,m_ActiveGrabPos{}
	,m_WindowDimensions{width, height}
{
	m_pWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
	SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
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
	
	if (!m_Grabbing)
	{
		m_ActiveGrabPos.x = 0;
		m_ActiveGrabPos.y = 0;
		m_StartGrabPos.x = 0;
		m_StartGrabPos.y = 0;
	}

	switch (event.type)
	{
	case SDL_QUIT:
		m_Exit = true;
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (SDL_BUTTON_LEFT == event.button.button)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			m_TargetPos.x = float(x);
			m_TargetPos.y = float(y);
		}

		if(SDL_BUTTON_RIGHT == event.button.button)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);

			if (!m_Grabbing)
			{
				m_StartGrabPos.x = float(x);
				m_StartGrabPos.y = float(y);
				m_Grabbing = true;
			}

		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (SDL_BUTTON_RIGHT == event.button.button)
		{
			//int x, y;
			//SDL_GetMouseState(&x, &y);
			//m_GrabRect.startPos = m_MousePos;
			//m_GrabRect.width = x - m_MousePos.x;
			//m_GrabRect.height = y - m_MousePos.y;

			std::cout << "stop grabbing" << "\n";

			m_Grabbing = false;
		}
		break;
	}

	if (m_Grabbing)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		m_ActiveGrabPos.x = float(x);
		m_ActiveGrabPos.y = float(y);
	}
}

void SDLUtil::Update()
{
	float width{ m_ActiveGrabPos.x - m_StartGrabPos.x };
	float height{ m_ActiveGrabPos.y - m_StartGrabPos.y };
	m_GrabRect.startPos = m_StartGrabPos;
	m_GrabRect.width = width;
	m_GrabRect.height = height;
}

void SDLUtil::RenderBackground() const
{
	SDL_SetRenderDrawColor(m_pRenderer, 177.f, 177.f, 177.f, 255.f);
	SDL_RenderClear(m_pRenderer);  //Back color
}

void SDLUtil::Render() const
{
	SDLUtil::DrawRect(m_GrabRect);
	SDL_RenderPresent(m_pRenderer);
}

void SDLUtil::DrawCircle(Utils::Vector2 centre, float radius) const
{
	const float diameter{ radius * 2.f };

	float x{ radius - 1 };
	float y{ 0.f };
	float tx{ 1.f };
	float ty{ 1.f };
	float error{ tx - diameter };

	while (x >= y)
	{
		SDL_RenderDrawPoint(m_pRenderer, centre.x + x, centre.y - y);
		SDL_RenderDrawPoint(m_pRenderer, centre.x + x, centre.y + y);
		SDL_RenderDrawPoint(m_pRenderer, centre.x - x, centre.y - y);
		SDL_RenderDrawPoint(m_pRenderer, centre.x - x, centre.y + y);
		SDL_RenderDrawPoint(m_pRenderer, centre.x + y, centre.y - x);
		SDL_RenderDrawPoint(m_pRenderer, centre.x + y, centre.y + x);
		SDL_RenderDrawPoint(m_pRenderer, centre.x - y, centre.y - x);
		SDL_RenderDrawPoint(m_pRenderer, centre.x - y, centre.y + x);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2.f;
		}

		if (error > 0)
		{
			--x;
			tx += 2.f;
			error += tx - diameter;
		}
	}
};

void SDLUtil::DrawRect(Utils::Rect rect) const
{
	SDL_RenderDrawLine(m_pRenderer, rect.startPos.x, rect.startPos.y, rect.startPos.x, rect.startPos.y + rect.height);
	SDL_RenderDrawLine(m_pRenderer, rect.startPos.x, rect.startPos.y, rect.startPos.x + rect.width, rect.startPos.y);
	SDL_RenderDrawLine(m_pRenderer, rect.startPos.x + rect.width, rect.startPos.y, rect.startPos.x + rect.width, rect.startPos.y + rect.height);
	SDL_RenderDrawLine(m_pRenderer, rect.startPos.x, rect.startPos.y + rect.height, rect.startPos.x + rect.width, rect.startPos.y + rect.height);
}

void SDLUtil::DrawLine(Utils::Vector2 point1, Utils::Vector2 point2) const
{
	SDL_RenderDrawLine(m_pRenderer, point1.x, point1.y, point2.x, point2.y);
}

Utils::Vector2 SDLUtil::GetMousePos() const
{
	return m_TargetPos;
}

Utils::Rect SDLUtil::GetGrabRect() const
{
	return m_GrabRect;
}

Utils::Vector2 SDLUtil::GetWindowDimensions() const
{
	return m_WindowDimensions;
}

void SDLUtil::ChangeColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(m_pRenderer, r, g, b, a);
}