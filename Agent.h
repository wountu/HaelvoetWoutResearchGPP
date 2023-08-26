#pragma once
#include "Utils.h"
#include "PathFinding.h"
#include <vector>

class SDLUtil;
class Group;

class Agent
{
public:
	Agent(SDLUtil* pSdl, Graph graph);
	~Agent();

	Agent(const Agent& other)			 = delete;
	Agent& operator=(const Agent& other) = delete;
	Agent(Agent&& other)				 = delete;
	Agent& operator=(Agent&& other)		 = delete;

	void Update(float elapsedSec, Utils::Vector2 target, Graph graph);
	void FollowCommander(Utils::Vector2 dir, float elapsedSec);
	void Render() const;
	void CheckIfGrabbed(Utils::Rect grabRect);

	bool IsActivated() const;
	bool HasArrived() const;
	Utils::Vector2 GetPosition() const;

	void SetGroup(Group* pGroup);
	
	float GetSpeed() const;

	void SetPath(std::vector<Utils::Vector2> path, Utils::Vector2 destination);
	std::vector<Utils::Vector2> CalculatePath(Utils::Vector2 target);

	Utils::Vector2 GetDir() const;
private:
	Graph m_Graph;
	Utils::Vector2 m_Position;
	const int m_MaxSpeed, m_MinSpeed;
	float m_Speed;
	Utils::Vector2 m_Target, m_Destination;
	std::vector<Utils::Vector2> m_Path;
	Utils::Vector2 m_Direction{ };

	bool m_Selected; //If he needs to react
	bool m_Arrived;
	bool m_IsInGroup;

	Group* m_pGroup;

	SDLUtil* m_pSDL;

	void HandleMovement(float elapsedSec);
};

