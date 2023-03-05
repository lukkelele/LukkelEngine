#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "LukkelEngine/Renderer/VertexArray.h"
#include "LukkelEngine/Renderer/VertexBuffer.h"
#include "LukkelEngine/Renderer/IndexBuffer.h"
#include "LukkelEngine/Renderer/Shader.h"
#include "LukkelEngine/Renderer/Texture.h"
#include "LukkelEngine/Scene/Components.h"
#include "LukkelEngine/Renderer/RigidBody.h"

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

	class Mesh
	{
	public:
		Mesh();
		Mesh(float vertices[], unsigned int indices[], const std::string& shaderPath,
				std::vector<int> vertbufLayout, unsigned int vertCount, unsigned int idxsCount);
		~Mesh() = default;

		void bind();
		void onUpdate(float ts, glm::mat4 viewProj = glm::mat4(1.0f));
		s_ptr<Shader> getShader() { return m_Shader; }
		s_ptr<Texture> getTexture() { return m_Texture; }
		s_ptr<IndexBuffer> getIndexBuffer() { return m_IBO; }

		glm::mat4 createModelMatrix(btTransform& transform);
		void createRigidBody(glm::vec3& dimensions = glm::vec3(0.5f, 0.5f, 0.5f),
							glm::vec3& offset = glm::vec3(0.0f, 0.0f, 0.0f),
							float mass = 5.0f, RigidBody::Type bodyType = RigidBody::Type::DYNAMIC);

		btRigidBody* getRigidBody() { return m_RigidBody->m_RigidBody; }
		int getShapeType() { return m_RigidBody->getShapeType(); }

		// Is accessed directly by the editor when modifying matrix values and other properties
		s_ptr<RigidBody> m_RigidBody;

	private:
		s_ptr<VertexArray> m_VAO;
		s_ptr<IndexBuffer> m_IBO;
		s_ptr<VertexBuffer> m_VBO;
		s_ptr<Shader> m_Shader;
		s_ptr<Texture> m_Texture;
	};
}