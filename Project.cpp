#include "Project.h"
#include "Formation.h"
#include "Agent.h"
#include "SDLUtil.h"
#include "Group.h"
#include <iostream>

Project::Project(SDLUtil* pSdl)
	:m_pFormation{ new Formation{} }
	,m_pAgent{new Agent{pSdl}}
	,m_pGroup{new Group{}}
{

}

Project::~Project()
{
	delete m_pFormation;
	m_pFormation = nullptr;

	delete m_pAgent;
	m_pAgent = nullptr;

	delete m_pGroup;
	m_pGroup = nullptr;
}

void Project::Update(float elapsedSec, Utils::Vector2 mousePos, Utils::Rect grabRect)
{
	if (m_pAgent->IsActivated())
		m_pGroup->AddAgent(m_pAgent);

	//m_pFormation->Update(elapsedSec);

	m_pAgent->Update(elapsedSec, mousePos, grabRect);
}

void Project::Render() const
{
	m_pAgent->Render();
}