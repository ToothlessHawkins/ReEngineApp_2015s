#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	//Using Base InitWindow method
	super::InitWindow("Instance Rendering");
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), vector3(0.0f, 0.0f, 0.0f), REAXISY);

	m_pMesh = new MyMesh();
	
	//Creating the Mesh points
	//1-1
	m_pMesh->AddVertexPosition(vector3(0.0f, 1.0f + 2.0f, 0.0f));
	m_pMesh->AddVertexColor(RERED);
	m_pMesh->AddVertexPosition(vector3(-1.0f, 0.0f + 2.0f, 0.0f));
	m_pMesh->AddVertexColor(REORANGE);
	m_pMesh->AddVertexPosition(vector3(1.0f, 0.0f + 2.0f, 0.0f));
	m_pMesh->AddVertexColor(REORANGE);
	
	//initializing the array
	m_nObjects = 9;

	//we need 16 floats for each object (each matrix has 16 floats)
	m_fMatrixArray = new  float[m_nObjects * 16];
	//initializing the whole spaces to the position at the origin just to play it safe
	const float* m4mvp1 = glm::value_ptr(glm::translate(vector3(0, 0 + 2, 0)));
	const float* m4mvp2 = glm::value_ptr(glm::translate(vector3(-1, -1 + 2, 0)));
	const float* m4mvp3 = glm::value_ptr(glm::translate(vector3(1, -1 + 2, 0)));

	const float* m4mvp4 = glm::value_ptr(glm::translate(vector3(0 - 2, 0, 0)));
	const float* m4mvp5 = glm::value_ptr(glm::translate(vector3(-1 - 2, -1, 0)));
	const float* m4mvp6 = glm::value_ptr(glm::translate(vector3(1 - 2, -1, 0)));

	const float* m4mvp7 = glm::value_ptr(glm::translate(vector3(0 + 2, 0, 0)));
	const float* m4mvp8 = glm::value_ptr(glm::translate(vector3(-1 + 2, -1, 0)));
	const float* m4mvp9 = glm::value_ptr(glm::translate(vector3(1 + 2, -1, 0)));
	//for (uint n = 0; n < m_nObjects; n++)
	//{
	//	const float* m4mvp = glm::value_ptr(
	//		glm::translate(vector3(n * 2, 0, 0)));
	//	memcpy(&m_fMatrixArray[n * 16], m4mvp, 16 * sizeof(float));
	//}
	memcpy(&m_fMatrixArray[0 * 16], m4mvp1, 16 * sizeof(float));
	memcpy(&m_fMatrixArray[1 * 16], m4mvp2, 16 * sizeof(float));
	memcpy(&m_fMatrixArray[2 * 16], m4mvp3, 16 * sizeof(float));
	memcpy(&m_fMatrixArray[3 * 16], m4mvp4, 16 * sizeof(float));
	memcpy(&m_fMatrixArray[4 * 16], m4mvp5, 16 * sizeof(float));
	memcpy(&m_fMatrixArray[5 * 16], m4mvp6, 16 * sizeof(float));
	memcpy(&m_fMatrixArray[6 * 16], m4mvp7, 16 * sizeof(float));
	memcpy(&m_fMatrixArray[7 * 16], m4mvp8, 16 * sizeof(float));
	memcpy(&m_fMatrixArray[8 * 16], m4mvp9, 16 * sizeof(float));
	
}

void AppClass::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->UpdateTime();

	//Is the arcball active?
	if (m_bArcBall == true)
		ArcBall();

	//Is the first person camera active?
	if (m_bFPC == true)
		CameraRotation();

	//Calculate Camera
	m_pCameraMngr->CalculateView();

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
										  //Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);

	//Compiling the mesh
	m_pMesh->CompileOpenGL3X();
}

void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window
	
	//Matrices from the camera
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	//m_pMesh->Render(m4Projection, m4View, IDENTITY_M4);//Rendering nObjects
	m_pMesh->RenderList(m4Projection, m4View, m_fMatrixArray, m_nObjects);

	m_pMeshMngr->Render();

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers


}

void AppClass::Release(void)
{
	SafeDelete(m_fMatrixArray);
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}
	super::Release();
}