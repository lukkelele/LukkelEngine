#pragma once
#include "LukkelEngine/Renderer/Material.h"
#include "LukkelEngine/Physics/Rigidbody.h"

#include <btBulletCollisionCommon.h>


namespace LukkelEngine {

	class ColliderShape
	{
	public:

		enum class ColliderType
		{
			Box, Sphere
		};

		virtual ~ColliderShape()
		{
		}

		ColliderType GetColliderType() const { return m_Type; }
		Material& GetMaterial() const { return *m_Material; }
		Rigidbody& GetRigidbody() { return m_Rigidbody; }

		virtual const char* GetShapeName() const = 0;

	protected:
		Rigidbody m_Rigidbody;
		ColliderType m_Type;
		s_ptr<Material> m_Material; // Pointer because the material can be shared by multiple shapes
	};

}