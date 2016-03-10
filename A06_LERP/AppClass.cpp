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

	m_nObjects = 11;
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

	/*display*/
	m_pSphere = new PrimitiveClass[m_nObjects];
	m_pMatrix = new matrix4[m_nObjects];

	//same method of displaying as the ice
	for (uint i = 0; i < m_nObjects; i++) {
		m_pSphere[i].GenerateSphere(0.1f,5,RERED);
		m_pMatrix[i] = glm::translate(waypoints[i]);
	}
	/*end display*/

	//initialize the flags that will indicate to the program where the model is
	v3current = waypoints[0];
	flag0 = true;
	flag1 = false;
	flag2 = false;
	flag3 = false;
	flag4 = false;
	flag5 = false;
	flag6 = false;
	flag7 = false;
	flag8 = false;
	flag9 = false;
	flag10 = false;
	numRounds = 0;
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

	m_pMeshMngr->SetModelMatrix(modelMat4, "WallEye");
#pragma region flags
	//this horrifying mess of if statements will be used to report the model's location
	//everytime it hits a waypoint, a flag boolean is thrown up
	if (v3current == waypoints[0]) {
		if (flag10 == true) {
			flag10 = false;
			numRounds++;
		}
		flag0 = true;
	}
	if (v3current == waypoints[1]) {
		flag0 = false;
		flag1 = true;
	}
	if (v3current == waypoints[2]) {
		flag1 = false;
		flag2 = true;
	}
	if (v3current == waypoints[3]) {
		flag2 = false;
		flag3 = true;
	}
	if (v3current == waypoints[4]) {
		flag3 = false;
		flag4 = true;
	}
	if (v3current == waypoints[5]) {
		flag4 = false;
		flag5 = true;
	}
	if (v3current == waypoints[6]) {
		flag5 = false;
		flag6 = true;
	}
	if (v3current == waypoints[7]) {
		flag6 = false;
		flag7 = true;
	}
	if (v3current == waypoints[8]) {
		flag7 = false;
		flag8 = true;
	}
	if (v3current == waypoints[9]) {
		flag8 = false;
		flag9 = true;
	}
	if (v3current == waypoints[10]) {
		flag9 = false;
		flag10 = true;
	}
#pragma endregion
	//fDuration = 5.0f;
#pragma region if statements to move the model based on flags
	//checks which flag is hit, scales time based on that, then lerps
	if (flag0 == true) {
		float fPercent = MapValue(static_cast<float>(fRunTime), 0.0f, 5.0f, 0.0f, 1.0f);

		v3current = glm::lerp(waypoints[0], waypoints[1], fPercent);
	}
	if (flag1 == true) {
		float fPercent = MapValue(static_cast<float>(fRunTime), 5.0f, 10.0f, 0.0f, 1.0f);

		v3current = glm::lerp(waypoints[1], waypoints[2], fPercent);
	}
	if (flag2 == true) {
		float fPercent = MapValue(static_cast<float>(fRunTime), 10.0f, 15.0f, 0.0f, 1.0f);

		v3current = glm::lerp(waypoints[2], waypoints[3], fPercent);
	}
	if (flag3 == true) {
		float fPercent = MapValue(static_cast<float>(fRunTime), 15.0f, 20.0f, 0.0f, 1.0f);

		v3current = glm::lerp(waypoints[3], waypoints[4], fPercent);
	}
	if (flag4 == true) {
		float fPercent = MapValue(static_cast<float>(fRunTime), 20.0f, 25.0f, 0.0f, 1.0f);

		v3current = glm::lerp(waypoints[4], waypoints[5], fPercent);
	}
	if (flag5 == true) {
		float fPercent = MapValue(static_cast<float>(fRunTime), 25.0f, 30.0f, 0.0f, 1.0f);

		v3current = glm::lerp(waypoints[5], waypoints[6], fPercent);
	}
	if (flag6 == true) {
		float fPercent = MapValue(static_cast<float>(fRunTime), 30.0f, 35.0f, 0.0f, 1.0f);

		v3current = glm::lerp(waypoints[6], waypoints[7], fPercent);
	}
	if (flag7 == true) {
		float fPercent = MapValue(static_cast<float>(fRunTime), 35.0f, 40.0f, 0.0f, 1.0f);

		v3current = glm::lerp(waypoints[7], waypoints[8], fPercent);
	}
	if (flag8 == true) {
		float fPercent = MapValue(static_cast<float>(fRunTime), 40.0f, 45.0f, 0.0f, 1.0f);

		v3current = glm::lerp(waypoints[8], waypoints[9], fPercent);
	}
	if (flag9 == true) {
		float fPercent = MapValue(static_cast<float>(fRunTime), 45.0f, 50.0f, 0.0f, 1.0f);

		v3current = glm::lerp(waypoints[9], waypoints[10], fPercent);
	}
	if (flag10 == true) {
		float fPercent = MapValue(static_cast<float>(fRunTime), 50.0f, 55.0f, 0.0f, 1.0f);

		v3current = glm::lerp(waypoints[10], waypoints[0], fPercent);
	}
#pragma endregion
	//move the model
	modelMat4 = glm::translate(v3current);

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
	//help to indicate the round
	if (numRounds != 0) {
		m_pMeshMngr->Print("round:");
		m_pMeshMngr->Print(std::to_string(numRounds), RERED);
	}
#pragma endregion
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
	
	//place checkpoints
	for (uint i = 0; i < m_nObjects; i++) {
		//m_pSphere[i].Render(); // this line is giving me an error telling me that the primitive class has no function called "render"
		//in class Alberto told me this was because I was using an old version of the engine but I've done everything I can short of deleting my fork
		//and making a whole new fork and it's still giving me that error. otherwise, this should make several red balls appear on the screen
		//in theory it's right, so maybe if you uncomment 
	};

	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	/*delete the arrays*/
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