#include "Group.h"
#include "Agent.h"

Group::Group()
	:m_Agents{}
	,m_Commander{}
	,m_State{stateGroup::StateBroken}
	,m_AllArrived{}
	,m_Speed{}
	,m_Formation{FormationType::Line}
	, m_FormationBroken{}
{

}

Group::~Group()
{
}

void Group::AddAgent(Agent* pAgent, Utils::Vector2 target)
{
	if (m_Agents.size() == 0)
	{
		m_Commander.pAgent = pAgent; //If we don't have agents in our group yet, make the first one our commander
		m_Commander.position = pAgent->GetPosition();
		m_Speed = pAgent->GetSpeed();
	}

	groupAgent agent{};
	agent.pAgent = pAgent;
	agent.position = pAgent->GetPosition();
	agent.target = target;

	for (const groupAgent& agentInVect : m_Agents)
	{
		if (agentInVect.pAgent == agent.pAgent)
			return;
	}

	m_State = stateGroup::StateForming;

	if (pAgent->GetSpeed() < m_Speed)
		m_Speed = pAgent->GetSpeed();

	agent.pAgent->SetGroup(this);

	m_Agents.push_back(agent);
}

void Group::RemoveAgent(Agent* pAgent)
{
	for (size_t idx{}; idx < m_Agents.size(); ++idx)
	{
		if (m_Agents[idx].pAgent == pAgent)
		{
			std::cout << "test" << "\n";
			m_Agents[idx] = m_Agents[m_Agents.size() - 1];
			m_Agents.pop_back();
		}
		
	}
}

void Group::Update(float elapsedSec, Utils::Vector2 target, Graph graph)
{
	//std::cout << m_Agents.size() << "\n";
	m_AllArrived = true; //Will reset back to false if a unit hasn't arrived yet

	if (m_State == stateGroup::StateForming)
	{
		for (size_t idx{}; idx < m_Agents.size(); ++idx)
		{
			m_Agents[idx].target = CalculateDestinationAgent(target, static_cast<int>(idx));

			//std::cout << m_Agents[idx].pAgent->GetPosition().x << ", " << m_Agents[idx].pAgent->GetPosition().y << "\n";

			m_Agents[idx].pAgent->Update(elapsedSec, m_Agents[idx].target, graph);
			if (!m_Agents[idx].pAgent->HasArrived())
				m_AllArrived = false;
		}

		if (m_AllArrived)
		{
			m_State = stateGroup::StateFormed;
			m_GroupsDestination = target;
		}
	}

	if (m_State == stateGroup::StateFormed)
	{
		if (m_GroupsDestination != target)
		{
			m_GroupsDestination = target;
			auto path = m_Commander.pAgent->CalculatePath(target);
			m_Commander.pAgent->SetPath(path, m_GroupsDestination);
		}

		if (!m_Commander.pAgent->HasArrived())
		{
			m_Commander.pAgent->Update(elapsedSec, m_GroupsDestination, graph);

			for (const auto& agent : m_Agents)
			{
				if (agent.pAgent != m_Commander.pAgent)
				{
					agent.pAgent->FollowCommander(m_Commander.pAgent->GetDir(), elapsedSec);
				}
			}
		}
		else
		{
			if (m_FormationBroken)
			{
				m_State = stateGroup::StateForming;
				m_FormationBroken = false;
			}
		}
	}

	//switch (m_State)
	//{
	//case stateGroup::StateBroken:
	//	std::cout << "broken" << "\n";
	//	break;
	//case stateGroup::StateForming:
	//	std::cout << "forming" << "\n";
	//	break;
	//case stateGroup::StateFormed:
	//	std::cout << "formed" << "\n";
	//	break;
	//}
}

void Group::Render() const
{
	//for (groupAgent agent : m_Agents)
	//{
	//	agent.pAgent->Render();
	//}
}

stateGroup Group::GetState() const
{
	return m_State;
}

float Group::GetSpeed()
{
	return m_Speed;
}

Utils::Vector2 Group::CalculateDestinationAgent(Utils::Vector2 startPos, int idx)
{
	Utils::Vector2 target{};
	const float angleRadTriangle = static_cast<float>(60.f * (M_PI / 180.f) * idx);
	const float agentDistance = 12;
	const int triangleRow = static_cast<int>(sqrt(idx));
	const float circleDegrees{ static_cast<float>((360 / m_Agents.size()) * (M_PI / 180.f))};

	switch (m_Formation)
	{
	case FormationType::Line:
		target.x = startPos.x + (agentDistance * idx);
		target.y = startPos.y;
		break;
	case FormationType::Triangle:
		target.x = startPos.x - (agentDistance * triangleRow) + ((idx - (triangleRow * triangleRow)) * agentDistance);
		target.y = startPos.y + agentDistance * triangleRow;
		break;
	case FormationType::Circle:
		if (m_Agents.size() == 1)
		{
			target = startPos;
		}
		else
		{
			target.x = startPos.x + agentDistance * std::cos(circleDegrees * idx);
			target.y = startPos.y + agentDistance * std::sin(circleDegrees * idx);
		}
		break;
	}

	return target;
}

void Group::ToggleFormation()
{
	int idx = static_cast<int>(m_Formation);
	++idx;
	idx %= 3;

	m_Formation = static_cast<FormationType>(idx);
	m_State = stateGroup::StateForming;
}

Agent* Group::GetCommander() const
{
	return m_Commander.pAgent;
}

void Group::BrokeFormation()
{
	m_FormationBroken = true;
}
