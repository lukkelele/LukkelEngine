#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Model/Mesh.h"
#include "LukkelEngine/Physics/Body/RigidBody.h"

#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"


namespace LukkelEngine {

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec3 tangent;
		glm::vec3 binormal;
		glm::vec2 texcoord;
	};

	class WorldObject
	{
	public:
		WorldObject() = default;
		WorldObject(Mesh mesh, RigidBody rigidBody);
		~WorldObject();

		void bind();
		void onUpdate(float ts, glm::mat4 viewProj);
		void remove();

		void addComponent(Entity& component);

		glm::mat4 getTransform(glm::mat4& viewProj);

	private:
		int m_ID; // Rigidbody identifier

		u_ptr<Mesh> m_Mesh;
		u_ptr<RigidBody> m_RigidBody;

		glm::vec3 m_Position{ 1.0f, 1.0f, 1.0f };
		glm::vec3 m_Scale{ 1.0f, 1.0f, 1.0f };
		glm::vec3 m_Translation{ 0.0f, 0.0f, 0.0f };
		glm::quat m_Rotation{ 1.0f, 0.0f, 0.0f, 0.0f };

		glm::vec3 m_Inertia{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_LinearVelocity{ 0.0f, 0.0f, 0.0f };
		glm::vec3 m_AngularVelocity{ 0.0f, 0.0f, 0.0f };
	};

}
