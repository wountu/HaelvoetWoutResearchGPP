#pragma once
#include "Utils.h"
#include <vector>
class Agent;

struct groupAgent {
	Agent* pAgent{};
	Utils::Vector2 position;
	Utils::Vector2 target;
	bool arrived;

	groupAgent() = default;
	groupAgent(Agent* pAgent, Utils::Vector2 position, Utils::Vector2 target);
};

enum class stateGroup
{
	StateBroken,
	StateForming,
	StateFormed
};

class Group
{
public:
	Group();
	~Group();

	Group(const Group& other)			 = delete;
	Group& operator=(const Group& other) = delete;
	Group(Group&& other)				 = delete;
	Group& operator=(Group&& other)		 = delete;

	void AddAgent(Agent* pAgent, Utils::Vector2 target);
	void RemoveAgent(Agent* pAgent);

	void Update(float elapsedSec, Utils::Vector2 target);
	void Render() const;
private:
	std::vector<groupAgent> m_Agents;
	groupAgent m_Commander;
	std::vector<Utils::Vector2> m_Targets;

	stateGroup m_State;
	bool m_AllArrived;
};

