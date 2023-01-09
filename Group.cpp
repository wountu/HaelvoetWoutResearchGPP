#include "Group.h"
#include "Agent.h"

Group::Group()
	:m_Agents{}
	,m_Commander{}
	,m_State{stateGroup::StateBroken}
	,m_AllArrived{}
{

}

Group::~Group()
{
}

void Group::AddAgent(Agent* pAgent, Utils::Vector2 target)
{
	if (m_Agents.size() == 0)
	{
		m_State = stateGroup::StateForming;
		m_Commander.pAgent = pAgent; //If we don't have agents in our group yet, make the first one our commander
		m_Commander.position = pAgent->GetPosition();
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

	m_Agents.push_back(agent);
}

void Group::RemoveAgent(Agent* pAgent)
{
	for (size_t idx{}; idx < m_Agents.size(); ++idx)
	{
		if (m_Agents[idx].pAgent == pAgent);
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
			m_Agents[idx].target.x = target.x + (20 * idx);
			m_Agents[idx].target.y = target.y;

			//std::cout << m_Agents[idx].pAgent->GetPosition().x << ", " << m_Agents[idx].pAgent->GetPosition().y << "\n";

			m_Agents[idx].pAgent->Update(elapsedSec, m_Agents[idx].target, graph);
			if (!m_Agents[idx].pAgent->HasArrived())
				m_AllArrived = false;
		}

		if (m_AllArrived)
			m_State = stateGroup::StateFormed;
	}

	if (m_State == stateGroup::StateFormed)
	{
		for (size_t idx{}; idx < m_Agents.size(); ++idx)
		{
			if (!m_Agents[idx].arrived);
			m_AllArrived = false;
			m_State = stateGroup::StateForming;
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