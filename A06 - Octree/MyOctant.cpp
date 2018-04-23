#include "MyOctant.h"
using namespace Simplex;

float Simplex::MyOctant::GetSize(void) { return m_fSize; }

Simplex::MyOctant::MyOctant(uint a_nMaxLevel, uint a_nIdealEntityCount)
{
}

Simplex::MyOctant::MyOctant(vector3 a_v3Center, float a_fSize)
{
	m_v3Center = a_v3Center;
	m_fSize = a_fSize;
	m_v3Max = a_v3Center + (vector3(a_fSize, a_fSize, a_fSize)/2.0f);
	m_v3Min = a_v3Center - (vector3(a_fSize, a_fSize, a_fSize)/2.0f);
	point1 = m_v3Max;
	point2 = vector3(m_v3Max.x, m_v3Min.y, m_v3Max.z);
	point3 = vector3(m_v3Min.x, m_v3Min.y, m_v3Max.z);
	point4 = vector3(m_v3Min.x, m_v3Max.y, m_v3Max.z);
	point5 = vector3(m_v3Max.x, m_v3Max.y, m_v3Min.z);
	point6 = vector3(m_v3Max.x, m_v3Min.y, m_v3Min.z);
	point7 = m_v3Min;
	point8 = vector3(m_v3Min.x, m_v3Max.y, m_v3Min.z);
	m_pMeshMngr = MeshManager::GetInstance();
	m_pEntityMngr = MyEntityManager::GetInstance();
}

Simplex::MyOctant::MyOctant(MyOctant const & other)
{
}

MyOctant& Simplex::MyOctant::operator=(MyOctant const & other)
{
	// TODO: insert return statement here
	return *this;
}

Simplex::MyOctant::~MyOctant(void)
{
}

void Simplex::MyOctant::Swap(MyOctant & other)
{
}


vector3 Simplex::MyOctant::GetCenterGlobal(void)
{
	return m_v3Center;
}

vector3 Simplex::MyOctant::GetMinGlobal(void)
{
	return m_v3Min;
}

vector3 Simplex::MyOctant::GetMaxGlobal(void)
{
	return m_v3Max;
}

void Simplex::MyOctant::IsColliding()
{
	for each (MyOctant* child in m_pChild) {
		if (child->m_EntityList.size() > 0) {
			for (uint i = 0; i < child->m_EntityList.size()-1; i++) {
				for (uint j = i + 1; j < child->m_EntityList.size(); j++) {
					m_pEntityMngr->GetEntity(child->m_EntityList[i])->IsColliding(m_pEntityMngr->GetEntity(child->m_EntityList[j]));
				}
			}
		}
	}
}

void Simplex::MyOctant::Display(uint a_nIndex, vector3 a_v3Color)
{
}

void Simplex::MyOctant::Display(vector3 a_v3Color)
{
	m_pMeshMngr->AddWireCubeToRenderList(glm::scale(IDENTITY_M4, vector3(m_fSize, m_fSize, m_fSize)) * glm::translate(IDENTITY_M4, m_v3Center), a_v3Color, RENDER_SOLID);
	m_pMeshMngr->AddWireSphereToRenderList(glm::translate(IDENTITY_M4, m_v3Center), a_v3Color, RENDER_SOLID);
	m_pMeshMngr->AddWireSphereToRenderList(glm::translate(IDENTITY_M4, point1), a_v3Color, RENDER_SOLID);
	m_pMeshMngr->AddWireSphereToRenderList(glm::translate(IDENTITY_M4, point2), a_v3Color, RENDER_SOLID);
	m_pMeshMngr->AddWireSphereToRenderList(glm::translate(IDENTITY_M4, point3), a_v3Color, RENDER_SOLID);
	m_pMeshMngr->AddWireSphereToRenderList(glm::translate(IDENTITY_M4, point4), a_v3Color, RENDER_SOLID);
	m_pMeshMngr->AddWireSphereToRenderList(glm::translate(IDENTITY_M4, point5), a_v3Color, RENDER_SOLID);
	m_pMeshMngr->AddWireSphereToRenderList(glm::translate(IDENTITY_M4, point6), a_v3Color, RENDER_SOLID);
	m_pMeshMngr->AddWireSphereToRenderList(glm::translate(IDENTITY_M4, point7), a_v3Color, RENDER_SOLID);
	m_pMeshMngr->AddWireSphereToRenderList(glm::translate(IDENTITY_M4, point8), a_v3Color, RENDER_SOLID);
}

void Simplex::MyOctant::DisplayLeafs(vector3 a_v3Color)
{
	m_pChild[0]->Display(a_v3Color);
	m_pChild[1]->Display(a_v3Color);
	m_pChild[2]->Display(a_v3Color);
	m_pChild[3]->Display(a_v3Color);
	m_pChild[4]->Display(a_v3Color);
	m_pChild[5]->Display(a_v3Color);
	m_pChild[6]->Display(a_v3Color);
	m_pChild[7]->Display(a_v3Color);
}

void Simplex::MyOctant::ClearEntityList(void)
{
	m_EntityList;
}

void Simplex::MyOctant::Subdivide(void)
{
	m_pChild[0] = new MyOctant(m_v3Center + (m_v3Max / 2.0f), m_fSize/2.0f);
	m_pChild[1] = new MyOctant(m_v3Center + vector3(m_fSize / 4.0f, -m_fSize / 4.0f, m_fSize / 4.0f), m_fSize / 2.0f);
	m_pChild[2] = new MyOctant(m_v3Center + vector3(-m_fSize / 4.0f, -m_fSize / 4.0f, m_fSize / 4.0f), m_fSize / 2.0f);
	m_pChild[3] = new MyOctant(m_v3Center + vector3(-m_fSize / 4.0f, m_fSize / 4.0f, m_fSize / 4.0f), -m_fSize / 2.0f);
	m_pChild[4] = new MyOctant(m_v3Center - (m_v3Max / 2.0f), m_fSize / 2.0f);
	m_pChild[5] = new MyOctant(m_v3Center - vector3(m_fSize / 4.0f, -m_fSize / 4.0f, m_fSize / 4.0f), m_fSize / 2.0f);
	m_pChild[6] = new MyOctant(m_v3Center - vector3(-m_fSize / 4.0f, -m_fSize / 4.0f, m_fSize / 4.0f), m_fSize / 2.0f);
	m_pChild[7] = new MyOctant(m_v3Center - vector3(-m_fSize / 4.0f, m_fSize / 4.0f, m_fSize / 4.0f), -m_fSize / 2.0f);
	std::cout << m_pChild[0]->GetSize() << std::endl;
	std::cout << m_pChild[0]->GetCenterGlobal().x << " " << m_pChild[0]->GetCenterGlobal().y << " " << m_pChild[0]->GetCenterGlobal().z << std::endl;
}

MyOctant * Simplex::MyOctant::GetChild(uint a_nChild)
{
	return m_pChild[a_nChild];
}

MyOctant * Simplex::MyOctant::GetParent(void)
{
	return m_pParent;
}

bool Simplex::MyOctant::IsLeaf(void)
{
	return false;
}

bool Simplex::MyOctant::ContainsMoreThan(uint a_nEntities)
{
	return false;
}

void Simplex::MyOctant::KillBranches(void)
{
}

void Simplex::MyOctant::ConstructTree(uint a_nMaxLevel)
{
}

void Simplex::MyOctant::AssignIDtoEntity(void)
{
}

uint Simplex::MyOctant::GetOctantCount(void)
{
	return uint();
}

void Simplex::MyOctant::placeEntities(void)
{
	for each (MyOctant* child in m_pChild) {
		/*std::cout << "Max: " << child->m_v3Max.x << " " << child->m_v3Max.y << " " << child->m_v3Max.z << std::endl;
		std::cout << "Min: " << child->m_v3Min.x << " " << child->m_v3Min.y << " " << child->m_v3Min.z << std::endl;*/
		for (int i = 0; i < m_pEntityMngr->GetEntityCount(); i++) {
			MyEntity* temp = m_pEntityMngr->GetEntity(i);
			if (temp->GetRigidBody()->GetCenterGlobal().x <= child->m_v3Max.x && temp->GetRigidBody()->GetCenterGlobal().x >= child->m_v3Min.x) {
				if (temp->GetRigidBody()->GetCenterGlobal().y <= child->m_v3Max.y && temp->GetRigidBody()->GetCenterGlobal().y >= child->m_v3Min.y) {
					if (temp->GetRigidBody()->GetCenterGlobal().z <= child->m_v3Max.z && temp->GetRigidBody()->GetCenterGlobal().z >= child->m_v3Min.z) {
						child->m_EntityList.push_back(i);
					}
				}
			}
		}
		std::cout << child->m_EntityList.size() << std::endl;
	}
}

void Simplex::MyOctant::Release(void)
{
}

void Simplex::MyOctant::ConstructList(void)
{
}
