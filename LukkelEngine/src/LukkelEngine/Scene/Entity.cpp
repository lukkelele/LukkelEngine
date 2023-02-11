#include "Entity.h"

namespace LukkelEngine {

	Entity::Entity()
	{
		s_ptr<VertexArray> m_VAO;
		s_ptr<VertexBuffer> m_VBO;
		s_ptr<IndexBuffer> m_IBO;
		// s_ptr<VertexBufferLayout> m_Layout;
	}

	Entity::~Entity()
	{
	}
}