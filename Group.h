#pragma once
#include "Utils.h"
#include "PathFinding.h"
#include <vector>
class Agent;

struct groupAgent {
	Agent* pAgent{};
	Utils::Vector2 position{};
	Utils::Vector2 target{};
	bool arrived{};

	groupAgent() = default;
	groupAgent(Agent* pAgent, Utils::Vector2 position, Utils::Vector2 target);
};

enum class stateGroup
{
	StateBroken,
	StateForming,
	StateFormed
};

enum class FormationType
{
	Line,
	Triangle,
	Circle
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

	void Update(float elapsedSec, Utils::Vector2 target, Graph graph);
	void Render() const;

	stateGroup GetState() const;
	float GetSpeed();

	Utils::Vector2 CalculateDestinationAgent(Utils::Vector2 startPos, int idx);
	
	void ToggleFormation();
private:
	std::vector<groupAgent> m_Agents;
	groupAgent m_Commander;
	std::vector<Utils::Vector2> m_Targets;
	Utils::Vector2 m_GroupsDestination;

	stateGroup m_State;
	FormationType m_Formation;

	bool m_AllArrived;

	float m_Speed;
};

