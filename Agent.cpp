#include "Agent.h"
#include "Utils.h"
#include "SDLUtil.h"
#include "PathFinding.h"
#include "Group.h"
#include <iostream>

Agent::Agent(SDLUtil* pSdl, Graph graph)
	:m_MaxSpeed{50}
	,m_MinSpeed{30}
	,m_Selected{false}
	,m_pSDL{pSdl}
	,m_Target{}
	,m_Arrived{false}
	,m_Path{}
	,m_Graph{graph}
	,m_IsInGroup{}
	,m_pGroup{nullptr}
	, m_pHelp{ new helper{} }
{
	m_Position.x = float(rand() % int(pSdl->GetWindowDimensions().x));
	m_Position.y = float(rand() % int(pSdl->GetWindowDimensions().y));

	m_Speed = static_cast<float>(m_MinSpeed + rand() % (m_MaxSpeed - m_MinSpeed));
	std::cout << m_Speed << "\n";
}

Agent::~Agent()
{

}

void Agent::Update(float elapsedSec, Utils::Vector2 target, Graph graph)
{
	//if (m_Path.size() == 0)
	//{
	//	m_Path = pathfinding::CalculatePath(m_Position, target, graph.nodes, m_Graph);
	//	m_Target = m_Path[0];
	//	std::cout << "Agent calculated the path\n";
	//}


	if (m_Destination != target && m_pGroup->GetState() == stateGroup::StateForming)
	{
		m_Destination = target;//Mousepos
		m_Path = pathfinding::CalculatePath(m_Position, target, graph.nodes, m_Graph);
		if (!m_Path.empty())
		{
			m_Target = m_Path[0];
			m_Arrived = false;
		}
	}

	if (m_Path.size() == 0) //At the right square
	{
		m_Target = m_Destination;
	}
	
	//if(m_Selected)
	HandleMovement(elapsedSec);

	//std::cout << m_Position.x << ", " << m_Position.y << "\n";
}

void Agent::FollowCommander(Utils::Vector2 dir, float elapsedSec)
{
	m_Position.x += dir.x * m_pGroup->GetSpeed() * elapsedSec;
	m_Position.y += dir.y * m_pGroup->GetSpeed() * elapsedSec;

	auto node = m_pHelp->GetNodeOnPoint(m_Position, m_Graph.nodes, 0.f, 0.f, 0, 0, Utils::Vector2{ m_Graph.nodes[0]->width, m_Graph.nodes[0]->height });
	if (node->cost > 5)
	{
		MoveToCommander(elapsedSec);
	}

	auto nodes = node->GetNeighbours(m_Graph.nodes, m_Graph.totalWidth, m_Graph.totalHeight, m_Graph.rows, m_Graph.cols);
	for (const auto& neigbour : nodes)
	{
		if (neigbour->cost < 5)
			continue;

		Utils::Rect agentRect{ m_Position, 5.f, 5.f };
		Utils::Rect tileRect{ neigbour->leftTop, neigbour->width, neigbour->height };

		if (m_pHelp->AreRectanglesColliding(agentRect, tileRect))
		{
			MoveToCommander(elapsedSec);
		}
	}
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

	m_Direction = m_Target - m_Position;
	const float length{ m_Direction.Length() };
	m_Direction.Normalize();

	if (length < acceptRadius)
	{
		if (m_Target == m_Destination)
			m_Arrived = true;

		m_Path.erase(std::remove(m_Path.begin(), m_Path.end(), m_Target), m_Path.end());

		if (m_Path.empty())
			return;

		m_Target = m_Path[0];

		return;
	}


	if (m_Arrived)
		return;

	float speed{};
	if (m_pGroup && m_pGroup->GetState() == stateGroup::StateFormed)
	{
		speed = m_pGroup->GetSpeed();
	}
	else speed = m_Speed;

	m_Position.x += m_Direction.x * (speed * elapsedSec);
	m_Position.y += m_Direction.y * (speed * elapsedSec);
}

void Agent::MoveToCommander(float elapsedSec)
{
	Utils::Vector2 toCom{ m_pGroup->GetCommander()->GetPosition() - m_Position };
	toCom.Normalize();

	m_Position.x += toCom.x * m_pGroup->GetSpeed() * elapsedSec;
	m_Position.y += toCom.y * m_pGroup->GetSpeed() * elapsedSec;

	m_pGroup->BrokeFormation();
}

bool Agent::IsActivated() const
{
	return m_Selected;
}

Utils::Vector2 Agent::GetPosition() const
{
	return m_Position;
}

void Agent::SetGroup(Group* pGroup)
{
	m_pGroup = pGroup;
}

float Agent::GetSpeed() const
{
	return m_Speed;
}

void Agent::SetPath(std::vector<Utils::Vector2> path, Utils::Vector2 destination)
{
	if(!path.empty())
	{
		m_Path = path;
		m_Target = m_Path[0];
	}

	m_Destination = destination;

	m_Arrived = false;
}

std::vector<Utils::Vector2> Agent::CalculatePath(Utils::Vector2 target)
{
	return pathfinding::CalculatePath(m_Position, target, m_Graph.nodes, m_Graph);
}

Utils::Vector2 Agent::GetDir() const
{
	return m_Direction;
}

bool Agent::HasArrived() const
{
	return m_Arrived;
}