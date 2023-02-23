#pragma once
#include "LukkelEngine/Core/UUID.h"
#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/Shader.h"
#include "LukkelEngine/Renderer/Texture.h"
#include "LukkelEngine/Physics/Body.h"

#include "btBulletDynamicsCommon.h"
#include "entt/entt.hpp"

namespace LukkelEngine {

	class Entity
	{
	public:
		Entity();
		virtual ~Entity();
		UUID getUUID() const { return m_UUID; }

		s_ptr<VertexArray> getVertexArray() const { return m_VAO; }
		s_ptr<VertexBuffer> getVertexBuffer() const { return m_VBO; }
		s_ptr<IndexBuffer> getIndexBuffer() const { return m_IBO; }
		VertexArray& getVertexArrayRef() const { return *m_VAO; }
		VertexBuffer& getVertexBufferRef() const { return *m_VBO; }
		IndexBuffer& getIndexBufferRef() const { return *m_IBO; }

		s_ptr<Shader> getShader() const { return m_Shader; }
		btRigidBody* getRigidBody() { return m_Body->getRigidBody(); }

		void setPosition(glm::vec3& position) { m_Position = position; }
		glm::mat4 getEntityTranslation();
		glm::vec3 getWorldTransform();
		void updateOrientation(glm::mat4 projectionMatrix);

	// TODO: Set these back to private
	public:
		s_ptr<VertexArray> m_VAO;
		s_ptr<VertexBuffer> m_VBO;
		s_ptr<IndexBuffer> m_IBO;
		s_ptr<Shader> m_Shader;
		s_ptr<Texture> m_Texture;
		s_ptr<Body> m_Body;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		UUID m_UUID;
	};

}