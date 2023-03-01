#include "LKpch.h"
#include "LukkelEngine/Math/Vector.h"


namespace LukkelEngine {

	template<typename T, typename Z>
	Z& Vector3::convertVec3(T)
	{
	}
		template<>
		glm::vec3& Vector3::convertVec3(btVector3 v1)
		{
			return glm::vec3{ v1.getX(), v1.getY(), v1.getZ() };
		}

		template<>
		btVector3& Vector3::convertVec3(glm::vec3 v1)
		{
			return btVector3{ v1.x, v1.y, v1.z };
		}


	btVector3 Vector3::btVec3(const glm::vec3& vec)
	{
		return btVector3{ vec.x, vec.y, vec.z };
	}

	glm::vec3 Vector3::glmVec3(const btVector3& vec)
	{
		return glm::vec3{ vec.getX(), vec.getY(), vec.getZ() };
	}

}
