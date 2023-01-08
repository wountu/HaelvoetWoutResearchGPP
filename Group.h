#pragma once
#include <vector>
class Agent;

class Group
{
public:
	Group();
	~Group();

	Group(const Group& other)			 = delete;
	Group& operator=(const Group& other) = delete;
	Group(Group&& other)				 = delete;
	Group& operator=(Group&& other)		 = delete;

	void AddAgent(Agent* pAgent);
private:
	std::vector<Agent*> m_pAgents;
	Agent* m_pCommander;
};

