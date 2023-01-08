#pragma once
#include "Utils.h"
class Formation;
class Agent;
class SDLUtil;
class Group;

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
	Agent* m_pAgent;
	Group* m_pGroup;
	Formation* m_pFormation;
};

