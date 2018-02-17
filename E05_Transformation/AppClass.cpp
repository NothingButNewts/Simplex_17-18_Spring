#include "AppClass.h"
void Application::InitVariables(void)
{
	//Make MyMesh objects
	for (int i = 0; i < 46; i++) {
		m_pMesh = new MyMesh();
		m_pMesh->GenerateCube(1.0f, C_BLACK);
		meshes.push_back(m_pMesh);
	}
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	/*Render all the meshes and move them*/
	static float fPos = 0.0f;
	m_m4Cube = glm::translate(vector3(fPos, 0.0f, 0.0f));
	meshes[0]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Cube * glm::translate(vector3(-5.0f, 5.0f, 0.0f)) * ToMatrix4(m_qArcBall));
	meshes[1]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Cube * glm::translate(vector3(1.0f, 5.0f, 0.0f)) * ToMatrix4(m_qArcBall));
	meshes[2]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Cube * glm::translate(vector3(-4.0f, 4.0f, 0.0f)) * ToMatrix4(m_qArcBall));
	meshes[3]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Cube * glm::translate(vector3(0.0f, 4.0f, 0.0f)) * ToMatrix4(m_qArcBall));
	float x = -5.0f;
	float y = 3.0f;
	for (int i = 4; i < 11; i++) {
		meshes[i]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Cube * glm::translate(vector3(x, y, 0.0f)) * ToMatrix4(m_qArcBall));
		x++;
	}
	x = -6.0f;
	y = 2.0f;
	meshes[11]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Cube * glm::translate(vector3(-6.0f, 2.0f, 0.0f)) * ToMatrix4(m_qArcBall));
	meshes[12]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Cube * glm::translate(vector3(-5.0f, 2.0f, 0.0f)) * ToMatrix4(m_qArcBall));
	meshes[13]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Cube * glm::translate(vector3(-3.0f, 2.0f, 0.0f)) * ToMatrix4(m_qArcBall));
	meshes[14]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Cube * glm::translate(vector3(-2.0f, 2.0f, 0.0f)) * ToMatrix4(m_qArcBall));
	meshes[15]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Cube * glm::translate(vector3(-1.0f, 2.0f, 0.0f)) * ToMatrix4(m_qArcBall));
	meshes[16]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Cube * glm::translate(vector3(1.0f, 2.0f, 0.0f)) * ToMatrix4(m_qArcBall));
	meshes[17]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Cube * glm::translate(vector3(2.0f, 2.0f, 0.0f)) * ToMatrix4(m_qArcBall));
	x = -7.0f;
	y = 1.0f;
	for (int i = 18; i < 29; i++) {
		meshes[i]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Cube * glm::translate(vector3(x, y, 0.0f)) * ToMatrix4(m_qArcBall));
		x += 1.0f;
	}
	meshes[29]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Cube * glm::translate(vector3(-7.0f, 0.0f, 0.0f)) * ToMatrix4(m_qArcBall));
	x = -5.0f;
	y = 0.0;
	for (int i = 30; i < 37; i++) {
		meshes[i]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Cube * glm::translate(vector3(x, y, 0.0f)) * ToMatrix4(m_qArcBall));
		x += 1.0f;
	}
	meshes[37]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Cube * glm::translate(vector3(3.0f, 0.0f, 0.0f)) * ToMatrix4(m_qArcBall));
	meshes[38]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Cube * glm::translate(vector3(-7.0f, -1.0f, 0.0f)) * ToMatrix4(m_qArcBall));
	meshes[39]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Cube * glm::translate(vector3(-5.0f, -1.0f, 0.0f)) * ToMatrix4(m_qArcBall));
	meshes[40]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Cube * glm::translate(vector3(1.0f, -1.0f, 0.0f)) * ToMatrix4(m_qArcBall));
	meshes[41]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Cube * glm::translate(vector3(3.0f, -1.0f, 0.0f)) * ToMatrix4(m_qArcBall));
	meshes[42]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Cube * glm::translate(vector3(-4.0f, -2.0f, 0.0f)) * ToMatrix4(m_qArcBall));
	meshes[43]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Cube * glm::translate(vector3(-3.0f, -2.0f, 0.0f)) * ToMatrix4(m_qArcBall));
	meshes[44]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Cube * glm::translate(vector3(-1.0f, -2.0f, 0.0f)) * ToMatrix4(m_qArcBall));
	meshes[45]->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), m_m4Cube * glm::translate(vector3(0.0f, -2.0f, 0.0f)) * ToMatrix4(m_qArcBall));
		
	//Update the position of the meshes by half of 1 float
	fPos += 0.05f;

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
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}
	//release GUI
	ShutdownGUI();
}