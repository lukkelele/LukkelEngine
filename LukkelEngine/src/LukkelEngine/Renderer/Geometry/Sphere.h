#pragma once
#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Math/Math.h"

#define LK_SPHERE_MIN_STACK_COUNT 2
#define LK_SPHERE_MIN_SECTOR_COUNT 3

namespace LukkelEngine::Geometry {

	struct Vertex
    {
        float x, y, z, s, t;
    };

	class Sphere
	{
	public:
		Sphere() = default;
		Sphere(float radius = 1.0f, int sectors = 36, int stacks = 18, bool smooth = true, int up = 3);
		~Sphere() = default;

		float getRadius() const { return m_Radius; }
		int getSectorCount() const { return m_SectorCount; }
		int getStackCount() const { return m_StackCount; }
		int getUpAxis() const { return m_UpAxis; }
		void Create(float radius, int sectorCount, int stackCount, bool smooth=true, int up=3);
		void setRadius(float radius);
		void setSectorCount(int sectorCount);
		void setStackCount(int stackCount);
		void setSmooth(bool smooth);
		void setUpAxis(int up);
		void reverseNormals();

		unsigned int getVertexCount() const{ return (unsigned int)m_Vertices.size() / 3; }
		unsigned int getNormalCount() const { return (unsigned int)m_Normals.size() / 3; }
		unsigned int getTexCoordCount() const { return (unsigned int)m_TexCoords.size() / 2; }
		unsigned int getIndexCount() const { return (unsigned int)m_Indices.size(); }
		unsigned int getLineIndexCount() const { return (unsigned int)m_LineIndices.size(); }
		unsigned int getTriangleCount() const { return getIndexCount() / 3; }
		unsigned int getVertexSize() const { return (unsigned int)m_Vertices.size() * sizeof(float); }
		unsigned int getNormalSize() const { return (unsigned int)m_Normals.size() * sizeof(float); }
		unsigned int getTexCoordSize() const { return (unsigned int)m_TexCoords.size() * sizeof(float); }
		unsigned int getIndexSize() const { return (unsigned int)m_Indices.size() * sizeof(unsigned int); }
		unsigned int getLineIndexSize() const { return (unsigned int)m_LineIndices.size() * sizeof(unsigned int); }
		const float* getVertices() const { return m_Vertices.data(); }
		const float* getNormals() const { return m_Normals.data(); }
		const float* getTexCoords() const { return m_TexCoords.data(); }
		const unsigned int* getIndices() const { return m_Indices.data(); }
		const unsigned int* getLineIndices() const  { return m_LineIndices.data(); }

		unsigned int getInterleavedVertexCount() const { return getVertexCount(); }    // # of vertices
		unsigned int getInterleavedVertexSize() const { return (unsigned int)m_InterleavedVertices.size() * sizeof(float); }    // # of bytes
		int getInterleavedStride() const { return m_InterleavedStride; }   // should be 32 bytes
		const float* getInterleavedVertices() const { return m_InterleavedVertices.data(); }

	private:
		void buildVerticesSmooth();
		void buildVerticesFlat();
		void buildInterleavedVertices();
		void changeUpAxis(int from, int to);
		void clearArrays();
		void addVertex(float x, float y, float z);
		void addNormal(float x, float y, float z);
		void addTexCoord(float s, float t);
		void addIndices(unsigned int i1, unsigned int i2, unsigned int i3);
		std::vector<float> computeFaceNormal(float x1, float y1, float z1,
											 float x2, float y2, float z2,
											 float x3, float y3, float z3);


	private:
        float m_Radius = 1.0f;
		int m_SectorCount = 36;                        
		int m_StackCount = 18;                        
		bool m_Smooth = true;
		int m_UpAxis = 3;

		std::vector<float> m_Vertices;
		std::vector<float> m_Normals;
		std::vector<float> m_TexCoords;
		std::vector<unsigned int> m_Indices;
		std::vector<unsigned int> m_LineIndices;

		std::vector<float> m_InterleavedVertices;
		int m_InterleavedStride;      
	};

}