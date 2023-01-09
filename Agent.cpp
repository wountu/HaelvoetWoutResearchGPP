#include "Agent.h"
#include "Utils.h"
#include "SDLUtil.h"
#include "PathFinding.h"
#include <iostream>

Agent::Agent(SDLUtil* pSdl)
	:m_MaxSpeed{50.f}
	,m_Selected{false}
	,m_pSDL{pSdl}
	,m_Target{}
	,m_Arrived{false}
	,m_Path{}
{
	m_Position.x = float(rand() % int(pSdl->GetWindowDimensions().x));
	m_Position.y = float(rand() % int(pSdl->GetWindowDimensions().y));
}

Agent::~Agent()
{

}

void Agent::Update(float elapsedSec, Utils::Vector2 target, Graph graph)
{
	if (m_Path.size() == 0)
	{
		m_Path = pathfinding::CalculatePath(target, graph.nodes);
	}

	if (m_Target != target)
	{
		m_Target = target;//Mousepos
		m_Path = pathfinding::CalculatePath(target, graph.nodes);

		std::cout << "test" << "\n";
	}
	
	//if(m_Selected)
	HandleMovement(elapsedSec);

	//std::cout << m_Position.x << ", " << m_Position.y << "\n";
}

void Agent::Render() const
{
	m_pSDL->ChangeColor(255, 255, 0, 255);
	m_pSDL->DrawCircle(m_Position, 5.f);
	m_pSDL->ChangeColor(255, 0, 0, 255);
	m_pSDL->DrawCircle(m_Target, 2.5f);
}

void Agent::CheckIfGrabbed(Utils::Rect grabRect)
{
	if (grabRect.width != 0 && grabRect.height != 0) //If we are not grabbing it is resetted to 0
	{
		if (Functions::IsPointInRect(m_Position, grabRect))
		{
			m_Selected = true;
		}
	}
}

void Agent::HandleMovement(float elapsedSec)
{
	//std::cout << m_Position.x << ", " << m_Position.y << "\n";
	const float acceptRadius{ 1.f };

	Utils::Vector2 dirVector{ m_Path[0] - m_Position};
	const float length{ dirVector.Length() };
	dirVector.Normalize();

	if (length < acceptRadius)
	{
		std::vector<Utils::Vector2> newPath{};
		m_Arrived = true;
		for (size_t idx{}; idx < m_Path.size(); ++idx)
		{
			if (idx == 0)
				continue;
			else
			{
				newPath.push_back(m_Path[idx]);
			}
		}
		m_Path = newPath;
	}
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

Utils::Vector2 Agent::GetPosition() const
{
	return m_Position;
}

bool Agent::HasArrived() const
{
	return m_Arrived;
}