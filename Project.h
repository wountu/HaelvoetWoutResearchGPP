#pragma once
#include "Utils.h"
#include "PathFinding.h"
#include <vector>

class Formation;
class Agent;
class SDLUtil;
class Group;
//class PathFinding;

class Project
{
public:
	//Constructor and destructor
	Project(SDLUtil* pSdl);
	~Project();

	//Rule of 5
	Project(const Project& other)			 = delete;
	Project& operator=(const Project& other) = delete;
	Project(Project&& other)				 = delete;
	Project& operator=(Project&& other)		 = delete;

	void Update(float elapsedSec, Utils::Vector2 mousePos, Utils::Rect grabRect);
	void Render() const;
private:
	std::vector<Agent*> m_pAgents{};
	Group* m_pGroup;
	Formation* m_pFormation;
	SDLUtil* m_pSdl;
	Graph m_Graph;

	bool m_RenderGraph;

	Utils::Vector2 m_DrawPoint;
	const int m_NrOfAgents{ 10 };
};

