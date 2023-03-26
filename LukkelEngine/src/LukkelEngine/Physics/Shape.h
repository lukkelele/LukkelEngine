#pragma once
#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Scene/Entity.h"

#include <btBulletCollisionCommon.h>


namespace LukkelEngine {

	class Shape
	{

		enum class ColliderType
		{
			Box, Sphere
		};


	public:

		virtual const char* GetShapeName() const = 0;

	protected:
		Entity m_Entity;

	};

}