#pragma once
#include "LukkelEngine/Renderer/Material.h"

namespace LukkelEngine {

	namespace Materials {

		class DebugMaterial : public Material
		{
		public:
			DebugMaterial()
			{
				m_Shader = create_s_ptr<Shader>("assets/shaders/flat.shader");
				LKLOG_WARN("Assigned DebugMaterial -> shader");
			}
			~DebugMaterial() = default;

		};

	}
}