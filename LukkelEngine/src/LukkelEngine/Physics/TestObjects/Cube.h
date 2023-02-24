#pragma once
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Scene/Components.h"

/*
	Test class for using components
*/
namespace LukkelEngine {

	class Cube : public Entity
	{
	public:
		Cube()
		{
			id = new IDComponent();
			mesh = new MeshComponent();
			body = new RigidBody3DComponent();
		}

		~Cube()
		{
			delete id;
			delete mesh;
			delete body;
		}
		
		IDComponent* id;
		MeshComponent* mesh;
		RigidBody3DComponent* body;
	};

}

