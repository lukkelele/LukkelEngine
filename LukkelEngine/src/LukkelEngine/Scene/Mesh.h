#pragma once
#include <glm/glm.hpp>

namespace LukkelEngine {

	enum MeshType
	{
		Triangle = 0,
		Quad = 1,
		Cube = 2,
		Sphere = 3
	};

	struct Vertex
	{
		glm::vec3 m_Pos;
		glm::vec3 m_Normal;
		glm::vec3 m_Color;
		glm::vec2 m_texCoords;
	};

	class Mesh
	{
	public:
		static void setTriangleData(std::vector<Vertex>& vertices, std::vector<uint32_t> &indices);
		static void setQuadData(std::vector<Vertex>& vertices, std::vector<uint32_t> &indices);
		static void setCubeData(std::vector<Vertex>& vertices, std::vector<uint32_t> &indices);
		static void setSphereData(std::vector<Vertex>& vertices, std::vector<uint32_t> &indices);
	};

}