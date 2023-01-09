#include "Group.h"
#include "Agent.h"

Group::Group()
	:m_Agents{}
	,m_Commander{}
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

void Group::Update(float elapsedSec, Utils::Vector2 target)
{
	//std::cout << m_Agents.size() << "\n";

	for (groupAgent agent : m_Agents)
	{
		agent.target = target;
		agent.pAgent->Update(elapsedSec, agent.target);
	}
}

void Group::Render() const
{
	//for (groupAgent agent : m_Agents)
	//{
	//	agent.pAgent->Render();
	//}
}