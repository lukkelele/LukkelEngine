#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "LukkelEngine/Renderer/Mesh.h"
#include "LukkelEngine/Physics/Body/RigidBody.h"
#include "LukkelEngine/Renderer/Material.h"
#include "LukkelEngine/Scene/Components.h"

namespace LukkelEngine {

	namespace UI {

		// static uint8_t colorsArraySize = 7;

		class Property
		{
		public:
			Property() = default;
			~Property() = default;

			static void vec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f);
			static void vec4Control(const std::string& label, glm::vec4& values, float min = 0.0f, float max = 1.0f, float resetValue = 0.0f, float columnWidth = 100.0f);
			static void colorMenu(Material& material, float columnWidth = 100.0f);

		private:

		};

	}

}