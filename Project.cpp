#include "Project.h"
#include "Formation.h"
#include "Agent.h"
#include "SDLUtil.h"
#include "Group.h"
#include <iostream>

Project::Project(SDLUtil* pSdl)
	:m_pFormation{ new Formation{} }
	,m_pGroup{new Group{}}
	,m_pSdl{pSdl}
	,m_DrawPoint{}
	,m_Graph{ Utils::Vector2{40.f, 40.f},pSdl->GetWindowDimensions().x, pSdl->GetWindowDimensions().y }
{
	for (size_t idx{}; idx < m_NrOfAgents; ++idx)
	{
		m_pAgents.push_back(new Agent{ pSdl, m_Graph });
	}
}

Project::~Project()
{
	delete m_pFormation;
	m_pFormation = nullptr;

	delete m_pGroup;
	m_pGroup = nullptr;

	for (Agent* pAgent : m_pAgents)
	{
		delete pAgent;
		pAgent = nullptr;
	}
}

void Project::Update(float elapsedSec, Utils::Vector2 mousePos, Utils::Rect grabRect)
{
	m_DrawPoint = mousePos;

	for (Agent* pAgent : m_pAgents)
	{
		pAgent->CheckIfGrabbed(grabRect);

		if (pAgent->IsActivated())
			m_pGroup->AddAgent(pAgent, mousePos);
		//else m_pGroup->RemoveAgent(pAgent); //It will check internally if that agent is in the group

		//pAgent->Update(elapsedSec, mousePos, grabRect);
	}

	m_pGroup->Update(elapsedSec, mousePos, m_Graph);
	//m_pFormation->Update(elapsedSec);
}

void Project::Render() const
{
	for (Agent* pAgent : m_pAgents)
	{
		pAgent->Render();
	}

	m_pSdl->DrawCircle(m_DrawPoint, 2.5f);

	if(m_pSdl->GetRenderGraph())
		m_Graph.Render(m_pSdl);
}
