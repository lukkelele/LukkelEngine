#pragma once
#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Renderer/Mesh.h"

#include <glm/glm.hpp>
#include <vector>


namespace LukkelEngine {

	namespace Utils {

		class Converter
		{
		public:
			Converter() = default;
			~Converter() = default;

			// float* convertVectorToFloatArray(const std::vector<glm::vec3>& vector)
			static std::vector<float> convertVectorToFloatVector(const std::vector<Vertex>& vector);
			static float* convertVectorToFloatArray(const std::vector<Vertex>& vector);

		};

		std::vector<float> Converter::convertVectorToFloatVector(const std::vector<Vertex>& vector)
		{
			std::vector<float> floatVector;
			for (const auto& v : vector)
			{
				floatVector.push_back(v.position.x);
				floatVector.push_back(v.position.y);
				floatVector.push_back(v.position.z);
			}
			return floatVector;
		}

		float* Converter::convertVectorToFloatArray(const std::vector<Vertex>& vector)
		{
			// Vertex is 15 elements total
			const int numElements = vector.size() * ( 3 * 4 + 2);
			float* floatArray = new float[numElements];
			int index = 0;

			for (const auto& v : vector) {
				floatArray[index++] = v.position.x;
				floatArray[index++] = v.position.y;
				floatArray[index++] = v.position.z;
			}
			return floatArray;
		}

	}
}