//Updated to use MyEntityManager by Nic Hartley & Isaac Walerstein

#include "AppClass.h"
using namespace Simplex;
void Application::InitVariables(void)
{
	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUp(vector3(0.0f, 3.0f, 13.0f), //Position
		vector3(0.0f, 3.0f, 12.0f),	//Target
		AXIS_Y);					//Up

	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)

	Emanager = new MyEntityManager();

	//Add entities to entity manager vector using AddEntity

	//creeper
	m_pCreeper = Emanager->AddEntity("Minecraft\\Creeper.obj", "Creeper");

	//steve
	m_pSteve = Emanager->AddEntity("Minecraft\\Steve.obj", "Steve");

	m_pCow = Emanager->AddEntity("Minecraft\\Cow.obj", "Cow");
	m_pZombie = Emanager->AddEntity("Minecraft\\Zombie.obj", "Zombie");
	m_pPig = Emanager->AddEntity("Minecraft\\Pig.obj", "Pig");
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the ArcBall active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Set model matrix for Steve and the other entities
	matrix4 mCreeper = glm::translate(m_v3Creeper) * ToMatrix4(m_qCreeper) * ToMatrix4(m_qArcBall);
	matrix4 mSteve = glm::translate(vector3(2.25f, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, -55.0f, AXIS_Z);
	matrix4 mCow = glm::translate(vector3(1.55f, 1.0f, 0.0f)) * glm::rotate(IDENTITY_M4, -55.0f, AXIS_Z);
	matrix4 mPig = glm::translate(vector3(0.0f, 0.5f, -1.5f)) * glm::rotate(IDENTITY_M4, -55.0f, AXIS_Z);
	matrix4 mZombie = glm::translate(vector3(1.55f, 0.0f, -3.0f)) * glm::rotate(IDENTITY_M4, -55.0f, AXIS_Z);

	//Set model matrices using entity manager SetModelMatrix function

	Emanager->SetModelMatrix(m_pCreeper, mCreeper);
	Emanager->SetModelMatrix(m_pSteve, mSteve);
	Emanager->SetModelMatrix(m_pCow, mCow);
	Emanager->SetModelMatrix(m_pPig, mPig);
	Emanager->SetModelMatrix(m_pZombie, mZombie);

	//Check collision using entity manager CheckCollisions function
	Emanager->CheckCollisions();

	//Add objects to render list using entity manager AddToRenderList function
	Emanager->AddToRenderList();

}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

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
	//release the creeper
	SafeDelete(m_pCreeper);

	//release Steve
	SafeDelete(m_pSteve);

	SafeDelete(m_pZombie);
	SafeDelete(m_pCow);
	SafeDelete(m_pPig);

	//release GUI
	ShutdownGUI();
}
