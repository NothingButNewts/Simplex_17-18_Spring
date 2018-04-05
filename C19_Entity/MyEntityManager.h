/*New class that can manage multiple entities
Written by Nic Hartley & Isaac Walerstein*/

#pragma once

#include "Simplex\Simplex.h"
#include "MyEntity.h"

namespace Simplex {

	class MyEntityManager
	{
		std::vector<MyEntity*> vEntities; //vector for holding entities
		std::map<String, MyEntity*> m_IDMap; //a map of the unique ID's
	public:
		MyEntityManager(); //default constructor
		~MyEntityManager(); //deinitializer

		MyEntity *AddEntity(String filename, String id); //method to add entities to the vector
		void CheckCollisions(); //method to check for collsiions between entities
		void AddToRenderList(); //method to add entities to the render list
		void SetModelMatrix(MyEntity* entity, matrix4 a_m4ToWorld); //method to assign model matrices to entities
	};
}

