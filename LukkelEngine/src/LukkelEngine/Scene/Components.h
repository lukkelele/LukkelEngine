#pragma once
#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/Shader.h"
#include "LukkelEngine/Renderer/Texture.h"
#include "LukkelEngine/Core/UUID.h"

#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "glm/glm.hpp"

#define LK_TEMPLATE_OBJECT_CUBE 4

namespace LukkelEngine{

	struct IDComponent
	{
		UUID ID;

		IDComponent() = default;
		IDComponent(const IDComponent&) = default;
	};

	struct TagComponent
	{
		std::string tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: tag(tag) {}
	};
	
	/**
	 * @brief Mesh component with bind functionality
	*/
	struct MeshComponent
	{
		float vertices_color[8 * 8] = {
		// Positions		  Texture coords    Color
		-0.5f, -0.5f,  0.5f,    0.0f, 1.0f,    1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,    1.0f, 0.0f,    0.2f, 0.5f, 0.0f,
		-0.5f,  0.5f,  0.5f,    1.0f, 1.0f,    1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,    1.0f, 1.0f,    0.3f, 0.5f, 0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, 1.0f,    0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,    0.0f, 1.0f,    0.0f, 0.5f, 0.5f,
		-0.5f,  0.5f, -0.5f,    1.0f, 1.0f,    0.7f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,    0.0f, 0.0f,    1.0f, 0.5f, 0.0f
		};
		unsigned int indices[6 * 6] = {
		//Top
		2, 6, 7,
		2, 3, 7,
		//Bottom
		0, 4, 5,
		0, 1, 5,
		//Left
		0, 2, 6,
		0, 4, 6,
		//Right
		1, 3, 7,
		1, 5, 7,
		//Front
		0, 2, 3,
		0, 1, 3,
		//Back
		4, 6, 7,
		4, 5, 7
	};

		s_ptr<VertexArray> va = nullptr;
		s_ptr<IndexBuffer> ib = nullptr;
		s_ptr<VertexBuffer> vb = nullptr;
		s_ptr<Shader> shader = nullptr;
		glm::vec3 pos{ 0.0f, 0.0f, 0.0f };

		MeshComponent()
		{
			va = create_s_ptr<VertexArray>();
			vb = create_s_ptr<VertexBuffer>(vertices_color, (sizeof(vertices_color) / (sizeof(float)) * sizeof(float)));
			ib = create_s_ptr<IndexBuffer>(indices, (sizeof(indices) / (sizeof(unsigned int)) * sizeof(unsigned int)));
			shader = create_s_ptr<Shader>("assets/shaders/3D/flat.shader");
			VertexBufferLayout layout;
			layout.push<float>(3);
			layout.push<float>(2);
			layout.push<float>(3);
			va->addBuffer(*vb, layout);
		}

		void updateOrientation(glm::mat4 modelTransform, glm::mat4 viewProjection)
		{
			shader->bind();
			shader->setUniformMat4f("u_Model", modelTransform);
			shader->setUniformMat4f("u_ViewProj", viewProjection);
		}
	};

	struct SpriteRendererComponent
	{
		glm::vec4 color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: color(color) {}
	};

	struct RigidBody3DComponent
	{
		enum class BodyType { STATIC = 0, DYNAMIC };

		btCollisionShape* shape = nullptr;
		float friction = 0.50f;
		float restitution = 0.50f;
		btScalar mass = 5.0f;
		btVector3 linearVelocity{ 0.0f, 0.0f, 0.0f };
		btVector3 angularVelocity{ 0.0f, 0.0f, 0.0f };
		btVector3 inertia{ 0.0f, 0.0f, 0.0f };
		btVector3 position{ 0.0f, 0.0f, 0.0f };
		btRigidBody* rigidBody = nullptr;
		btDefaultMotionState* motionState;

		RigidBody3DComponent() = default;
		RigidBody3DComponent(uint8_t template_object)
		{
			float xOffset = 0.0f, yOffset = 4.0f, zOffset = 0.0f;
			float length = 0.5f, height = 0.5f, depth = 0.5f;
			shape = new btBoxShape(btVector3(length, height, depth));
			motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
							  btVector3(xOffset, yOffset, zOffset)));
			shape->calculateLocalInertia(mass, inertia);
			btRigidBody::btRigidBodyConstructionInfo boxBodyConstructionInfo(mass, motionState, shape, inertia);
			rigidBody = new btRigidBody(boxBodyConstructionInfo);
			rigidBody->setFriction(friction);
			rigidBody->setRestitution(restitution);
		}

		void printPosition()
		{
			auto pos = rigidBody->getCenterOfMassPosition();
			auto s = rigidBody->getCenterOfMassPosition();
			auto body = rigidBody;
			LKLOG_TRACE("Mass position : ({0}, {1}, {2})  | Mass: {3} | nullptr == {4}", pos.getX(), pos.getY(), pos.getZ(), mass, body == nullptr);
		}

		// Get model transform
		glm::mat4 getModelTransform(float scale = 1.0f)
		{
			glm::mat4 model(1.0f);
			btTransform transform;
			
			rigidBody->getMotionState()->getWorldTransform(transform);

			btVector3 translate = transform.getOrigin();
			btQuaternion rotation = transform.getRotation();

			glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), rotation.getAngle(),
				glm::vec3(rotation.getAxis().getX(), rotation.getAxis().getY(), rotation.getAxis().getZ()));

			glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
			glm::mat4 transMat = glm::translate(glm::mat4(1.0f), glm::vec3(translate.getX(), translate.getY(), translate.getZ()));
			glm::mat4 modelMatrix = transMat * rotMat * scaleMat;
			return modelMatrix;
		}
	};


	template<typename... Component>
	struct ComponentGroup
	{
	};

	using AllComponents =
		ComponentGroup<IDComponent,
					   TagComponent,
					   SpriteRendererComponent,
					   RigidBody3DComponent>;

}
