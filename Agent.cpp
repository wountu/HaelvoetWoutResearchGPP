#include "Agent.h"
#include "Utils.h"
#include "SDLUtil.h"
#include <iostream>

Agent::Agent(SDLUtil* pSdl)
	:m_Position{50.f, 50.f}
	,m_MaxSpeed{50.f}
	,m_Selected{false}
	,m_pSDL{pSdl}
	,m_Target{}
	,m_Arrived{false}
{
}

Agent::~Agent()
{

}

void Agent::Update(float elapsedSec, Utils::Vector2 target, Utils::Rect grabRect)
{
	m_Target = target;//Mousepos

	if(m_Selected)
		HandleMovement(elapsedSec);

	if (grabRect.width != 0 && grabRect.height != 0) //If we are not grabbing it is resetted to 0
	{
		if (Functions::IsPointInRect(m_Position, grabRect))
		{
			m_Selected = true;
		}
		else m_Selected = false;
	}

	std::cout << m_Selected << "\n";
}

void Agent::Render() const
{
	m_pSDL->DrawCircle(m_Position, 5.f);
	m_pSDL->DrawCircle(m_Target, 2.5f);
}

void Agent::HandleMovement(float elapsedSec)
{
	//std::cout << m_Position.x << ", " << m_Position.y << "\n";
	const float acceptRadius{ 2.f };

	Utils::Vector2 dirVector{ m_Target - m_Position };
	const float length{ dirVector.Length() };
	dirVector.Normalize();

	if (length < acceptRadius)
		m_Arrived = true;
	else m_Arrived = false;

	if (m_Arrived)
		return;

	m_Position.x += dirVector.x * (m_MaxSpeed * elapsedSec);
	m_Position.y += dirVector.y * (m_MaxSpeed * elapsedSec);
}

bool Agent::IsActivated() const
{
	return m_Selected;
}