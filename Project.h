#pragma once
class Project
{
public:
	//Constructor and destructor
	Project();
	~Project();

	//Rule of 5
	Project(const Project& other)			 = delete;
	Project& operator=(const Project& other) = delete;
	Project(Project&& other)				 = delete;
	Project& operator=(Project&& other)		 = delete;

	void Update(float elapsedSec);
	void Render() const;
private:
};

