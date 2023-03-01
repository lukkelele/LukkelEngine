#pragma once
#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Scene/Components.h"
#include "LukkelEngine/Scene/Scene.h"

#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"


namespace LukkelEngine {

	class ObjectHandler
	{
	public:
		static void addCube(Scene& scene, const std::string name);
		static void addFloor(Scene& scene, const std::string name);

	private:
		std::string floorShaderPath = "assets/shaders/3D/default.shader";
		std::string cubeShaderPath = "assets/shaders/3D/flat.shader";
		std::vector<int> cubeLayout  = { 3, 2, 3 };
		std::vector<int> floorLayout = { 3, 3 };
	};
}
