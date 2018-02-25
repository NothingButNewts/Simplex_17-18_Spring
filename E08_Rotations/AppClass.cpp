#include "AppClass.h"
void Application::InitVariables(void)
{
	//Set the position and target of the camera
	//(I'm at [0,0,10], looking at [0,0,0] and up is the positive Y axis)
	m_pCameraMngr->SetPositionTargetAndUp(AXIS_Z * 10.0f, ZERO_V3, AXIS_Y);

	m_pMesh = new MyMesh();
	m_pMesh->GenerateCone(1.0f, 2.0f, 6, C_WHITE);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Get a timer
	static uint uClock = m_pSystem->GenClock();
	float fTimer = m_pSystem->GetTimeSinceStart(uClock);
	float fDeltaTime = m_pSystem->GetDeltaTime(uClock);


#pragma region SLERP
	if (false)
	{
		quaternion q1;
		quaternion q2 = glm::angleAxis(359.9f, vector3(0.0f, 0.0f, 1.0f));
		float fPercentage = MapValue(fTimer, 0.0f, 5.0f, 0.0f, 1.0f);
		quaternion qSLERP = glm::mix(q1, q2, fPercentage);
		m_m4Mesh = glm::toMat4(qSLERP);
	}
#pragma endregion
#pragma region translate vector orientation into a matrix
	if (false)
	{
		matrix4 m4OrientX = glm::rotate(IDENTITY_M4, m_v3Orientation.x, vector3(1.0f, 0.0f, 0.0f));
		matrix4 m4OrientY = glm::rotate(IDENTITY_M4, m_v3Orientation.y, vector3(0.0f, 1.0f, 0.0f));
		matrix4 m4OrientZ = glm::rotate(IDENTITY_M4, m_v3Orientation.z, vector3(0.0f, 0.0f, 1.0f));

		matrix4 m4Orientation = m4OrientX * m4OrientY * m4OrientZ;
		m_m4Mesh = glm::toMat4(m_qOrientation);
	}
#pragma endregion
#pragma region orientation using quaternions
	if (true)
	{
		m_m4Mesh = glm::toMat4(m_qOrientation);
	}
#pragma endregion
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();
	
	m_pMesh->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Mesh);

	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();

	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//release model
	SafeDelete(m_pMesh);

	//release GUI
	ShutdownGUI();
}
