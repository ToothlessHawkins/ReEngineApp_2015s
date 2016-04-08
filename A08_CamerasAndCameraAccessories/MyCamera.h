#pragma once
//Repo link: https://github.com/ToothlessHawkins/ReEngineApp_2015s
#include <SFML\Graphics.hpp>
#include "RE\ReEngAppClass.h"

using namespace ReEng;

class MyCamera
{
public:
	static MyCamera& getInstance()
	{
		static MyCamera    instance;
		return instance;
	}
	/*
	static void ReleaseInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	};*/




	//glm::mat4 camTransMat;
	glm::vec3 camPosition = glm::vec3(0.0f, 0.0f, 1.0f); // camera position - set to a point on the positive Z axis
	glm::vec3 camTarget = glm::vec3(0.0f, 0.0f, 0.0f); //what the camera is looking at - origin
	glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f); // the up v3 of the camera - positive y axis

	CAMERAMODE m_nMode = CAMERAMODE::CAMPERSP; // camera mode - persp/ortho
	matrix4 m_m4View = matrix4(1.0f); // view mat4 - set to identity
	matrix4 m_m4Projection = matrix4(1.0f); // projection m4 - set to identity


	glm::vec3 m_v3Forward = glm::vec3(0.0f, 0.0f, -1.0f); // the foward v3 of the camera - negative z axis?
	glm::vec3 m_v3Rightward = glm::vec3(1.0f, 0.0f, 0.0f); // the right v3 of the camera - positive x axis?

	glm::quat quaternerizor = glm::quat(1.0f, 0.0f, 0.0f, 0.0f); // quaternion for orientation calculations


	matrix4 GetViewMatrix(void);

	matrix4 GetProjection(bool bOrthographic);

	void MyCamera::SetPosition(glm::vec3 v3Pos);

	void MyCamera::SetTarget(glm::vec3 v3Target);

	void MyCamera::SetUp(glm::vec3 v3Up);

	void MyCamera::MoveForward(float fIncrement);

	void MyCamera::MoveSideways(float fIncrement);

	void MyCamera::MoveVertical(float fIncrement);

	void MyCamera::ChangePitch(float fIncrement);

	void MyCamera::ChangeRoll(float fIncrement);

	void MyCamera::ChangeYaw(float fIncrement);

private:
	MyCamera() {} // constructor
	MyCamera(MyCamera const&);       // Don't Implement - copy consttuctor
	void operator=(MyCamera const&); // Don't implement - assignment operator
	
};