#pragma once
#include "Utils.h"
#include "PathFinding.h"
#include <vector>

class SDLUtil;

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
	void Render() const;
	void CheckIfGrabbed(Utils::Rect grabRect);

	bool IsActivated() const;
	bool HasArrived() const;
	Utils::Vector2 GetPosition() const;
private:
	Graph m_Graph;
	Utils::Vector2 m_Position;
	const float m_MaxSpeed;
	Utils::Vector2 m_Target, m_Destination;
	std::vector<Utils::Vector2> m_Path;

	bool m_Selected; //If he needs to react
	bool m_Arrived;

	SDLUtil* m_pSDL;

	void HandleMovement(float elapsedSec);
};

