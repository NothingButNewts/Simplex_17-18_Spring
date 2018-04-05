/*New class that can manage multiple entities
Written by Nic Hartley & Isaac Walerstein*/

#include "MyEntityManager.h"

namespace Simplex {

	//default constructor
	MyEntityManager::MyEntityManager()
	{
	}

	//deinitializer that releases entity pointers
	MyEntityManager::~MyEntityManager()
	{
		for (auto ptr : vEntities) {
			delete ptr;
		}
	}

	//add an entity to the map and vector
	MyEntity *MyEntityManager::AddEntity(String filename, String id) {
		if (m_IDMap.find(filename) != m_IDMap.end()) {
			return nullptr;
		}
		MyEntity *made = new MyEntity(filename, id);
		vEntities.push_back(made);
		m_IDMap[id] = made;
		return made;
	}

	//check for collisions between all objeccts (causes some lag)
	void MyEntityManager::CheckCollisions()
	{
		for (int i = 0; i < vEntities.size(); ++i) {
			for (int j = i + 1; j < vEntities.size(); ++j) {
				vEntities[i]->IsColliding(vEntities[j]);
			}
		}
	}

	//add all entities to the render list
	void MyEntityManager::AddToRenderList()
	{
		for (auto p : vEntities) {
			p->AddToRenderList(true);
		}
	}

	//set the model matrix for an entity given a "to world" matrix
	void MyEntityManager::SetModelMatrix(MyEntity* entity, matrix4 a_m4ToWorld) {
		entity->SetModelMatrix(a_m4ToWorld);
	}
}
