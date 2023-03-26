#include "LKpch.h"
#include "LukkelEngine/Debug/Debugger.h"


namespace LukkelEngine {

	template<typename T>
	void Debugger::PrintVec2(T vector, const std::string name)
	{
	}
		template<>
		void Debugger::PrintVec2<glm::vec2>(glm::vec2 vector, const std::string name)
		{
			LKLOG_WARN("VEC2 {2}: ({0}, {1})", vector.x, vector.y, name);
		}


	template<typename T>
	void Debugger::PrintVec3(T vector, const std::string name)
	{
	}
		template<>
		void Debugger::PrintVec3<btVector3>(btVector3 vector, const std::string name)
		{
			LKLOG_WARN("VEC3 {3}: ({0}, {1}, {2})", vector.getX(), vector.getY(), vector.getZ(), name);
		}

		template<>
		void Debugger::PrintVec3<glm::vec3>(glm::vec3 vector, const std::string name)
		{
			LKLOG_WARN("VEC3 {3}: ({0}, {1}, {2})", vector.x, vector.y, vector.z, name);
		}


}