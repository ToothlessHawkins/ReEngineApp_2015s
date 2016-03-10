#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");

	fDuration = 1.0f;

	/*list of locations to define movement of sprite*/
	waypoints = new vector3[m_nObjects];
	waypoints[0] = vector3(-4.0f, -2.0f, 5.0f);
	waypoints[1] = vector3(1.0f, -2.0f, 5.0f);
	waypoints[2] = vector3(-3.0f, -1.0f, 3.0f);
	waypoints[3] = vector3(2.0f, -1.0f, 3.0f);
	waypoints[4] = vector3(-2.0f, 0.0f, 0.0f);
	waypoints[5] = vector3(3.0f, 0.0f, 0.0f);
	waypoints[6] = vector3(-1.0f, 1.0f, -3.0f);
	waypoints[7] = vector3(4.0f, 1.0f, -3.0f);
	waypoints[8] = vector3(0.0f, 2.0f, -5.0f);
	waypoints[9] = vector3(5.0f, 2.0f, -5.0f);
	waypoints[10] = vector3(1.0f, 3.0f, -5.0f);

	m_nObjects = 11;
	m_pSphere = new PrimitiveClass[m_nObjects];
	m_pMatrix = new matrix4[m_nObjects];

	/**/
	for (uint i = 0; i < m_nObjects; i++) {
		m_pSphere[i].GenerateSphere(0.5f,5,RERED);
		m_pMatrix[i] = glm::translate(waypoints[i]);
	}
}

void AppClass::Update(void)
{
#pragma region Does not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static double fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan; 
#pragma endregion

#pragma region Your Code goes here
	m_pMeshMngr->SetModelMatrix(IDENTITY_M4/*insert your matrix here*/, "WallEye");

	//vector3 v3Current = glm::lerp(v3Start, v3End, fPercent);


#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}
	
	/**/
	for (uint i = 0; i < m_nObjects; i++) {
		m_pSphere[i].Render();
	}

	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	/*delete the array*/
	if (waypoints != nullptr) {
		delete[] waypoints;
		waypoints = nullptr;
	}
	if (m_pSphere != nullptr) {
		delete[] m_pSphere; //"new[]" corresponds to "delete[]", "new()" corresponds to "delete"
		m_pSphere = nullptr;
	}

	if (m_pMatrix != nullptr) {
		delete[] m_pMatrix; //"new[]" corresponds to "delete[]", "new()" corresponds to "delete"
		m_pMatrix = nullptr;
	}

	super::Release(); //release the memory of the inherited fields
}