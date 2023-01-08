#include "Group.h"
#include "Agent.h"

Group::Group()
	:m_pAgents{}
	,m_pCommander{nullptr}
{

}

Group::~Group()
{
	for (Agent* pAgent : m_pAgents)
	{
		delete pAgent;
		pAgent = nullptr;
	}
}

void Group::AddAgent(Agent* pAgent)
{
	if (m_pAgents.size() == 0)
	{
		m_pCommander = pAgent; //If we don't have agents in our group yet, make the first one our commander
	}
	m_pAgents.push_back(pAgent);
}