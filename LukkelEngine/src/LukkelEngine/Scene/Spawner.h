#pragma once
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Scene/Components.h"
#include "LukkelEngine/Scene/Scene.h"
#include "LukkelEngine/Renderer/Mesh.h"
#include "LukkelEngine/Renderer/Shapes.h"

#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"


namespace LukkelEngine {

	class Spawner
	{
	public:
		Spawner() = default;
		~Spawner() = default;

		enum class Items
		{
			LINE,
			CUBE,
			TRIANGLE,
			SPHERE
		};
			
		static Entity& createCube(Scene& scene, const std::string& = "");

		static void createGround(Scene& scene, const std::string& = "");
		static void createBarrel(Scene& scene, const std::string& = "");
		static void createPyramid(Scene& scene, const std::string& = "");

		static void addConstraint(Scene& scene, Entity entity);


	private:

	};

}