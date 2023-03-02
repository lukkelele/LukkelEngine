#include "LKpch.h"
#include "LukkelEngine/Debug/Debugger.h"


namespace LukkelEngine {

	template<typename T>
	void Debugger::printVec2(T vector, const std::string name)
	{
	}
		template<>
		void Debugger::printVec2<glm::vec2>(glm::vec2 vector, const std::string name)
		{
			LKLOG_WARN("VEC2 {2}: ({0}, {1})", vector.x, vector.y, name);
		}


	template<typename T>
	void Debugger::printVec3(T vector, const std::string name)
	{
	}
		template<>
		void Debugger::printVec3<btVector3>(btVector3 vector, const std::string name)
		{
			LKLOG_WARN("VEC3 {3}: ({0}, {1}, {2})", vector.getX(), vector.getY(), vector.getZ(), name);
		}

		template<>
		void Debugger::printVec3<glm::vec3>(glm::vec3 vector, const std::string name)
		{
			LKLOG_WARN("VEC3 {3}: ({0}, {1}, {2})", vector.x, vector.y, vector.z, name);
		}


}