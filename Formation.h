#pragma once
#include "Utils.h"
class Formation
{
public:
	Formation();
	~Formation();

	Formation(const Formation& other)			 = delete;
	Formation& operator=(const Formation& other) = delete;              
	Formation(Formation&& other)				 = delete;                     
	Formation& operator=(Formation&& other)		 = delete;  

	void Update(float elapsedSec);
	void Render() const;
private:
	Utils::Vector2 m_Centroid{};
	float m_MaxSpeed{};
	
};

