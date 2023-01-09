#pragma once
#include "Utils.h"

class SDLUtil;

class Agent
{
public:
	Agent(SDLUtil* pSdl);
	~Agent();

	Agent(const Agent& other)			 = delete;
	Agent& operator=(const Agent& other) = delete;
	Agent(Agent&& other)				 = delete;
	Agent& operator=(Agent&& other)		 = delete;

	void Update(float elapsedSec, Utils::Vector2 target);
	void Render() const;
	void CheckIfGrabbed(Utils::Rect grabRect);

	bool IsActivated() const;
	Utils::Vector2 GetPosition() const;
private:
	Utils::Vector2 m_Position;
	const float m_MaxSpeed;
	bool m_Selected; //If he needs to react
	Utils::Vector2 m_Target;
	SDLUtil* m_pSDL;
	bool m_Arrived;

	void HandleMovement(float elapsedSec);
};

