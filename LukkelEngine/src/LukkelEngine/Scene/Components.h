#pragma once
#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/Shader.h"
#include "LukkelEngine/Renderer/Texture.h"
#include "LukkelEngine/Core/UUID.h"

#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "glm/glm.hpp"

#define LK_TEMPLATE_OBJECT_CUBE 4
#define LK_TEMPLATE_OBJECT_FLOOR 5

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
		s_ptr<VertexArray> va = nullptr;
		s_ptr<IndexBuffer> ib = nullptr;
		s_ptr<VertexBuffer> vb = nullptr;
		s_ptr<Shader> shader = nullptr;
		glm::vec3 pos{ 0.0f, 0.0f, 0.0f };

		MeshComponent() = default;

		MeshComponent(float vertices[], unsigned int indices[], const std::string& shaderPath,
							std::vector<int> vertbufLayout, unsigned int vertCount, unsigned int idxsCount)
		{
			va = create_s_ptr<VertexArray>();
			vb = create_s_ptr<VertexBuffer>(vertices, vertCount * sizeof(float));
			ib = create_s_ptr<IndexBuffer>(indices, idxsCount * sizeof(unsigned int));
			shader = create_s_ptr<Shader>(shaderPath);
			VertexBufferLayout layout;

			for (int num : vertbufLayout) // VertexBufferLayout
				layout.push<float>(num);

			va->addBuffer(*vb, layout);
		}

		void updateOrientation(glm::mat4 modelTransform, glm::mat4 viewProjection)
		{
			shader->bind();
			shader->setUniformMat4f("u_Model", modelTransform);
			shader->setUniformMat4f("u_ViewProj", viewProjection);
		}

		glm::mat4 getTranslation()
		{
			return glm::translate(glm::mat4(1.0f), pos);
		}

	};

	struct RigidBody3DComponent
	{
		btVector3 dimensions{ 1.0f, 1.0f, 1.0f };
		btCollisionShape* shape = nullptr;
		float friction = 1.0f;
		float restitution = 0.20f;
		btScalar mass = 0.0f;
		btVector3 inertia{ 0.0f, 0.0f, 0.0f };
		btVector3 pos{ 0.0f, 0.0f, 0.0f };
		btRigidBody* rigidBody = nullptr;
		btDefaultMotionState* motionState = nullptr;

		RigidBody3DComponent(btVector3& dimensions, btVector3& offset, float mass = 1.0f)
		{
			shape = new btBoxShape(dimensions);
			motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), offset));
			// btDefaultMotionState* MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), offset));
			shape->calculateLocalInertia(mass, inertia);
			// btRigidBody::btRigidBodyConstructionInfo boxBodyConstructionInfo(mass, new btDefaultMotionState(), shape, inertia);
			btRigidBody::btRigidBodyConstructionInfo boxBodyConstructionInfo(mass, motionState, shape, inertia);
			rigidBody = new btRigidBody(boxBodyConstructionInfo);
			rigidBody->setFriction(friction);
			rigidBody->setRestitution(restitution);
		}

		void printPosition()
		{
			auto pos = rigidBody->getCenterOfMassPosition();
			auto body = rigidBody;
			LKLOG_TRACE("Mass position : ({0}, {1}, {2})  | Mass: {3} ", pos.getX(), pos.getY(), pos.getZ(), mass);
		}

		glm::mat4 getModelTransform(glm::mat4 meshTranslation, float scale = 1.0f)
		{
			btTransform transform;
			glm::mat4 model(1.0f);
			rigidBody->getMotionState()->getWorldTransform(transform);

			btVector3 translate = transform.getOrigin();
			btQuaternion rotation = transform.getRotation();

			glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), rotation.getAngle(),
				glm::vec3(rotation.getAxis().getX(), rotation.getAxis().getY(), rotation.getAxis().getZ()));

			glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
			// glm::mat4 transMat = glm::translate(glm::mat4(1.0f), glm::vec3(translate.getX(), translate.getY(), translate.getZ()));
			glm::mat4 transMat = glm::translate(meshTranslation, glm::vec3(translate.getX(), translate.getY(), translate.getZ()));
			glm::mat4 modelMatrix = transMat * rotMat * scaleMat;
			return modelMatrix;
		}
	};


	struct SpriteComponent
	{
		glm::vec4 color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteComponent() = default;
		SpriteComponent(const SpriteComponent&) = default;
		SpriteComponent(const glm::vec4& color)
			: color(color) {}
	};



	template<typename... Component>
	struct ComponentGroup
	{
	};

	using AllComponents =
		ComponentGroup<IDComponent,
					   TagComponent,
					   SpriteComponent,
					   RigidBody3DComponent>;

}
