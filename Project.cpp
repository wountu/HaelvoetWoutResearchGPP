#include "Project.h"
#include "Formation.h"
#include "Agent.h"
#include "SDLUtil.h"
#include <iostream>

Project::Project(SDLUtil* pSdl)
	:m_pFormation{ new Formation{} }
	,m_pAgent{new Agent{pSdl}}
{

}

Project::~Project()
{
	delete m_pFormation;
	m_pFormation = nullptr;

	delete m_pAgent;
	m_pAgent = nullptr;
}

void Project::Update(float elapsedSec, Utils::Vector2 mousePos, Utils::Rect grabRect)
{
	m_pFormation->Update(elapsedSec);
	m_pAgent->Update(elapsedSec, mousePos, grabRect);
}

void Project::Render() const
{
	m_pAgent->Render();
}