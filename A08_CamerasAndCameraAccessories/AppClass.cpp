#include "AppClass.h"
#include "MyCamera.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("A08_Camera"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	//Reset the selection to -1, -1
	m_selection = std::pair<int, int>(-1, -1);

	////Set the camera position
	//m_pCameraMngr->SetPositionTargetAndView(
	//	vector3(0.0f, 2.5f, 15.0f),//Camera position
	//	vector3(0.0f, 2.5f, 0.0f),//What Im looking at
	//	REAXISY);//What is up

	//Load a model onto the Mesh manager
	//m_pMeshMngr->LoadModel("Lego\\Unikitty.bto", "Unikitty");

	//Generate the Cone
	m_pCone = new PrimitiveClass();
	m_pCone->GenerateCone(1.0f, 2.0f, 10, RERED);

	//Generate the cube
	m_pCube = new PrimitiveClass();
	m_pCube->GenerateCube(1.0f, REPURPLE);

	//make the camera
	myCam = &MyCamera::getInstance();

}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	////First person camera movement
	//if (m_bFPC == true)
	//	CameraRotation();

	//Call the arcball method
	//ArcBall();
	
	//Set the model matrix for the first model to be the arcball
	//m_pMeshMngr->SetModelMatrix(ToMatrix4(m_qArcBall), 0);
	
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	//printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
<<<<<<< HEAD:A08_CamerasAndCameraAccessories/AppClass.cpp
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
	
	//Render the cone in perspective mode, 
	matrix4 m4Proj = myCam->GetProjection(false);
	matrix4 m4View = myCam->GetViewMatrix();

	m_pCone->Render(m4Proj, m4View, IDENTITY_M4);

	//Render the cube
	m_pCube->Render(m4Proj, m4View, IDENTITY_M4);

=======
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
>>>>>>> 00680e2f8635d9f9f2a635f595b7b37a88d4d800:06_Octree/AppClass.cpp
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ResetRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	delete m_pCone;
	delete m_pCube;

	// myCam->release;

	super::Release(); //release the memory of the inherited fields
}