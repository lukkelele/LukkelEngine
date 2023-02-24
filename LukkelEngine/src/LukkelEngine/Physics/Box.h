#pragma once

#include "LukkelEngine/Physics/Collider.h"


namespace LukkelEngine {


	class Box : public Collider
	{
	public:
		// TODO: Add quaternion rotation values for the constructor
		Box(float length = 0.5f, float height = 0.5f, float depth = 0.5f,
			float xOffset = 0.0f, float yOffset = 3.0f, float zOffset = 0.0f,
			btScalar mass = 1.0f, btVector3 inertia = { 0, 0, 0 },
			float friction = 0.8f, float restitution = 1.0f);
		~Box();

		// void reposition(btVector3 pos, btVector3 orientation) override;
	};

}