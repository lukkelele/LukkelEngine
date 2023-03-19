#include "LKpch.h"
#include "LukkelEngine/Renderer/Geometry/Sphere.h"


namespace LukkelEngine::Geometry {

	Sphere::Sphere(float radius, int sector, int stack, bool smooth, int up)
	{

	}


	void Sphere::create(float radius, int sectors, int stacks, bool smooth, int up)
	{
		if(radius > 0) 
			this->m_Radius = radius;

		if(sectors >= LK_SPHERE_MIN_SECTOR_COUNT)
			this->m_SectorCount = sectors;

		if (stacks >= LK_SPHERE_MIN_STACK_COUNT)
			this->m_StackCount = stacks;

		this->m_Smooth = smooth;
		if(up >= 1 || up <= 3)
			this->m_UpAxis = up; // FIXME: MIGHT CAUSE PROBLEMS

		// if(smooth) buildVerticesSmooth();
		// else buildVerticesFlat();

		buildVerticesFlat();
	}

	void Sphere::addVertex(float x, float y, float z)
	{
		m_Vertices.push_back(x);
		m_Vertices.push_back(y);
		m_Vertices.push_back(z);
	}

	void Sphere::addNormal(float nx, float ny, float nz)
	{
		m_Normals.push_back(nx);
		m_Normals.push_back(ny);
		m_Normals.push_back(nz);
	}

	void Sphere::addTexCoord(float s, float t)
	{
		m_TexCoords.push_back(s);
		m_TexCoords.push_back(t);
	}

	void Sphere::addIndices(unsigned int i1, unsigned int i2, unsigned int i3)
	{
		m_Indices.push_back(i1);
		m_Indices.push_back(i2);
		m_Indices.push_back(i3);
	}

	void Sphere::buildVerticesFlat()
	{
		const float PI = acos(-1.0f);

		std::vector<Vertex> tmpVertices;

		float sectorStep = 2 * PI / m_SectorCount;
		float stackStep = PI / m_StackCount;
		float sectorAngle, stackAngle;

		// compute all vertices first, each vertex contains (x,y,z,s,t) except normal
		for (int i = 0; i <= m_StackCount; ++i)
		{
			stackAngle = PI / 2 - i * stackStep;    // starting from pi/2 to -pi/2
			float xy = m_Radius * cosf(stackAngle); // r * cos(u)
			float z = m_Radius * sinf(stackAngle);  // r * sin(u)

			// Add (sectorCount+1) vertices per stack
			// The first and last vertices have same position and normal but different tex coords
			for (int j = 0; j <= m_SectorCount; ++j)
			{
				sectorAngle = j * sectorStep;           // starting from 0 to 2pi

				Vertex vertex;
				vertex.x = xy * cosf(sectorAngle);      // x = r * cos(u) * cos(v)
				vertex.y = xy * sinf(sectorAngle);      // y = r * cos(u) * sin(v)
				vertex.z = z;                           // z = r * sin(u)
				vertex.s = (float)j / m_SectorCount;        // s
				vertex.t = (float)i / m_StackCount;         // t
				tmpVertices.push_back(vertex);
			}
		}
		// clear memory of prev arrays
		clearArrays();

		Vertex v1, v2, v3, v4;   // 4 vertex positions and tex coords
		std::vector<float> n;    // 1 face normal

		int i, j, k, vi1, vi2;
		int index = 0;           // index for vertex

		for(i = 0; i < m_StackCount; ++i)
		{
			vi1 = i * (m_SectorCount + 1);                // index of tmpVertices
			vi2 = (i + 1) * (m_SectorCount + 1);

			for (j = 0; j < m_SectorCount; ++j, ++vi1, ++vi2)
			{
				// get 4 vertices per sector
				//  v1--v3
				//  |    |
				//  v2--v4
				v1 = tmpVertices[vi1];
				v2 = tmpVertices[vi2];
				v3 = tmpVertices[vi1 + 1];
				v4 = tmpVertices[vi2 + 1];

				// If 1st stack and last stack, store only 1 triangle per sector
				// Otherwise, store 2 triangles (quad) per sector
				if (i == 0) // A triangle for first stack ==========================
				{
					// put a triangle
					addVertex(v1.x, v1.y, v1.z);
					addVertex(v2.x, v2.y, v2.z);
					addVertex(v4.x, v4.y, v4.z);

					// put tex coords of triangle
					addTexCoord(v1.s, v1.t);
					addTexCoord(v2.s, v2.t);
					addTexCoord(v4.s, v4.t);

					// put normal
					n = computeFaceNormal(v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v4.x, v4.y, v4.z);
					for (k = 0; k < 3; ++k)  // Same normals for 3 vertices
					{
						addNormal(n[0], n[1], n[2]);
					}

					// put indices of 1 triangle
					addIndices(index, index + 1, index + 2);

					// indices for line (first stack requires only vertical line)
					m_LineIndices.push_back(index);
					m_LineIndices.push_back(index + 1);

					index += 3;     // for next
				}
				else if (i == (m_StackCount - 1)) // a triangle for last stack =========
				{
					// put a triangle
					addVertex(v1.x, v1.y, v1.z);
					addVertex(v2.x, v2.y, v2.z);
					addVertex(v3.x, v3.y, v3.z);

					// put tex coords of triangle
					addTexCoord(v1.s, v1.t);
					addTexCoord(v2.s, v2.t);
					addTexCoord(v3.s, v3.t);

					// put normal
					n = computeFaceNormal(v1.x,v1.y,v1.z, v2.x,v2.y,v2.z, v3.x,v3.y,v3.z);
					for(k = 0; k < 3; ++k)  // same normals for 3 vertices
					{
						addNormal(n[0], n[1], n[2]);
					}

					// Put indices of 1 triangle
					addIndices(index, index+1, index+2);
					// Indices for lines (last stack requires both vert/hori lines)
					m_LineIndices.push_back(index);
					m_LineIndices.push_back(index+1);
					m_LineIndices.push_back(index);
					m_LineIndices.push_back(index+2);
					index += 3;     // for next
				}
				else // 2 triangles for others ====================================
				{
					// Put quad vertices: v1-v2-v3-v4
					addVertex(v1.x, v1.y, v1.z);
					addVertex(v2.x, v2.y, v2.z);
					addVertex(v3.x, v3.y, v3.z);
					addVertex(v4.x, v4.y, v4.z);

					// Put tex coords of quad
					addTexCoord(v1.s, v1.t);
					addTexCoord(v2.s, v2.t);
					addTexCoord(v3.s, v3.t);
					addTexCoord(v4.s, v4.t);

					// Put normal
					n = computeFaceNormal(v1.x,v1.y,v1.z, v2.x,v2.y,v2.z, v3.x,v3.y,v3.z);
					for(k = 0; k < 4; ++k)  // same normals for 4 vertices
					{
						addNormal(n[0], n[1], n[2]);
					}
					// Put indices of quad (2 triangles)
					addIndices(index, index + 1, index + 2);
					addIndices(index + 2, index + 1, index + 3);
					// Indices for lines
					m_LineIndices.push_back(index);
					m_LineIndices.push_back(index+1);
					m_LineIndices.push_back(index);
					m_LineIndices.push_back(index+2);

					index += 4;     // for next
				}
			}
		}

		// generate interleaved vertex array as well
		buildInterleavedVertices();

		// change up axis from Z-axis to the given
		if(this->m_UpAxis != 3)
			changeUpAxis(3, this->m_UpAxis);
	}

	void Sphere::buildVerticesSmooth()
	{
		const float PI = acos(-1.0f);
		// Clear memory of prev arrays
		clearArrays();

		float x, y, z, xy;                              // vertex position
		float nx, ny, nz, lengthInv = 1.0f / m_Radius;  // normal
		float s, t;                                     // texCoord

		float sectorStep = 2 * PI / m_SectorCount;
		float stackStep = PI / m_StackCount;
		float sectorAngle, stackAngle;

		for(int i = 0; i <= m_StackCount; ++i)
		{
			stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
			xy = m_Radius * cosf(stackAngle);             // r * cos(u)
			z = m_Radius * sinf(stackAngle);              // r * sin(u)

			// add (sectorCount+1) vertices per stack
			// the first and last vertices have same position and normal, but different tex coords
			for(int j = 0; j <= m_SectorCount; ++j)
			{
				sectorAngle = j * sectorStep;           // starting from 0 to 2pi

				// vertex position
				x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
				y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
				addVertex(x, y, z);

				// normalized vertex normal
				nx = x * lengthInv;
				ny = y * lengthInv;
				nz = z * lengthInv;
				addNormal(nx, ny, nz);

				// vertex tex coord between [0, 1]
				s = (float)j / m_SectorCount;
				t = (float)i / m_StackCount;
				addTexCoord(s, t);
			}
		}

		//  Indices
		//  k1--k1+1
		//  |  / |
		//  | /  |
		//  k2--k2+1
		unsigned int k1, k2;
		for(int i = 0; i < m_StackCount; ++i)
		{
			k1 = i * (m_SectorCount + 1);     // beginning of current stack
			k2 = k1 + m_SectorCount + 1;      // beginning of next stack

			for (int j = 0; j < m_SectorCount; ++j, ++k1, ++k2)
			{
				// 2 triangles per sector excluding 1st and last stacks
				if(i != 0)
					addIndices(k1, k2, k1+1);   // k1---k2---k1+1

				if(i != (m_StackCount-1))
					addIndices(k1+1, k2, k2+1); // k1+1---k2---k2+1

				// vertical lines for all stacks
				m_LineIndices.push_back(k1);
				m_LineIndices.push_back(k2);
				if (i != 0)  // horizontal lines except 1st stack
				{
					m_LineIndices.push_back(k1);
					m_LineIndices.push_back(k1 + 1);
				}
			}
		}

		// generate interleaved vertex array as well
		buildInterleavedVertices();

		// change up axis from Z-axis to the given
		if(this->m_UpAxis != 3)
			changeUpAxis(3, this->m_UpAxis);
	}

	void Sphere::buildInterleavedVertices()
	{
		std::vector<float>().swap(m_InterleavedVertices);

		std::size_t i, j;
		std::size_t count = m_Vertices.size();
		for(i = 0, j = 0; i < count; i += 3, j += 2)
		{
			m_InterleavedVertices.push_back(m_Vertices[i]);
			m_InterleavedVertices.push_back(m_Vertices[i + 1]);
			m_InterleavedVertices.push_back(m_Vertices[i + 2]);

			m_InterleavedVertices.push_back(m_Normals[i]);
			m_InterleavedVertices.push_back(m_Normals[i + 1]);
			m_InterleavedVertices.push_back(m_Normals[i + 2]);

			m_InterleavedVertices.push_back(m_TexCoords[j]);
			m_InterleavedVertices.push_back(m_TexCoords[j + 1]);
		}
	}

	void Sphere::changeUpAxis(int from, int to)
	{
		// Initial transform matrix cols
		float tx[] = {1.0f, 0.0f, 0.0f};    // x-axis (left)
		float ty[] = {0.0f, 1.0f, 0.0f};    // y-axis (up)
		float tz[] = {0.0f, 0.0f, 1.0f};    // z-axis (forward)

		// X -> Y
		if(from == 1 && to == 2)
		{
			tx[0] =  0.0f; tx[1] =  1.0f;
			ty[0] = -1.0f; ty[1] =  0.0f;
		}
		// X -> Z
		else if(from == 1 && to == 3)
		{
			tx[0] =  0.0f; tx[2] =  1.0f;
			tz[0] = -1.0f; tz[2] =  0.0f;
		}
		// Y -> X
		else if(from == 2 && to == 1)
		{
			tx[0] =  0.0f; tx[1] = -1.0f;
			ty[0] =  1.0f; ty[1] =  0.0f;
		}
		// Y -> Z
		else if(from == 2 && to == 3)
		{
			ty[1] =  0.0f; ty[2] =  1.0f;
			tz[1] = -1.0f; tz[2] =  0.0f;
		}
		//  Z -> X
		else if(from == 3 && to == 1)
		{
			tx[0] =  0.0f; tx[2] = -1.0f;
			tz[0] =  1.0f; tz[2] =  0.0f;
		}
		// Z -> Y
		else
		{
			ty[1] =  0.0f; ty[2] = -1.0f;
			tz[1] =  1.0f; tz[2] =  0.0f;
		}

		std::size_t i, j;
		std::size_t count = m_Vertices.size();
		float vx, vy, vz;
		float nx, ny, nz;
		for(i = 0, j = 0; i < count; i += 3, j += 8)
		{
			// transform vertices
			vx = m_Vertices[i];
			vy = m_Vertices[i+1];
			vz = m_Vertices[i+2];
			m_Vertices[i]   = tx[0] * vx + ty[0] * vy + tz[0] * vz;   // x
			m_Vertices[i+1] = tx[1] * vx + ty[1] * vy + tz[1] * vz;   // y
			m_Vertices[i+2] = tx[2] * vx + ty[2] * vy + tz[2] * vz;   // z

			// transform normals
			nx = m_Normals[i];
			ny = m_Normals[i+1];
			nz = m_Normals[i+2];
			m_Normals[i]   = tx[0] * nx + ty[0] * ny + tz[0] * nz;   // nx
			m_Normals[i+1] = tx[1] * nx + ty[1] * ny + tz[1] * nz;   // ny
			m_Normals[i+2] = tx[2] * nx + ty[2] * ny + tz[2] * nz;   // nz

			// trnasform interleaved array
			m_InterleavedVertices[j]   = m_Vertices[i];
			m_InterleavedVertices[j+1] = m_Vertices[i+1];
			m_InterleavedVertices[j+2] = m_Vertices[i+2];
			m_InterleavedVertices[j+3] = m_Normals[i];
			m_InterleavedVertices[j+4] = m_Normals[i+1];
			m_InterleavedVertices[j+5] = m_Normals[i+2];
		}
	}

	std::vector<float> Sphere::computeFaceNormal(float x1, float y1, float z1,  // Vector 1
												 float x2, float y2, float z2,  // Vector 2
												 float x3, float y3, float z3)  // Vector 3
	{
		const float EPSILON = 0.000001f;

		std::vector<float> normal(3, 0.0f);     // default return value (0,0,0)
		float nx, ny, nz;

		// find 2 edge vectors: v1-v2, v1-v3
		float ex1 = x2 - x1;
		float ey1 = y2 - y1;
		float ez1 = z2 - z1;
		float ex2 = x3 - x1;
		float ey2 = y3 - y1;
		float ez2 = z3 - z1;

		// cross product: e1 x e2
		nx = ey1 * ez2 - ez1 * ey2;
		ny = ez1 * ex2 - ex1 * ez2;
		nz = ex1 * ey2 - ey1 * ex2;

		// normalize only if the length is > 0
		float length = sqrtf(nx * nx + ny * ny + nz * nz);
		if(length > EPSILON)
		{
			// normalize
			float lengthInv = 1.0f / length;
			normal[0] = nx * lengthInv;
			normal[1] = ny * lengthInv;
			normal[2] = nz * lengthInv;
		}

		return normal;
	}

}