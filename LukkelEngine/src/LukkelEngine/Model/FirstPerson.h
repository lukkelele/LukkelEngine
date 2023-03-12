#pragma once
#include "LukkelEngine/Core/Base.h"
#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Scene/Components.h"


namespace LukkelEngine {

	namespace Model {

		struct FirstPersonProperties
		{
			std::string name;
			float speed;
			float jumpDistance;
			float mass;
		};
		// Will implement health, projectile manipulation using raycasts
		// and other necessary components for an interactive first person model

		class FirstPerson
		{
		public:
			FirstPerson();
			FirstPerson(FirstPersonProperties& props, Scene& scene);
			~FirstPerson() = default;

		private:
			FirstPersonProperties m_Props;

		};

	}

}