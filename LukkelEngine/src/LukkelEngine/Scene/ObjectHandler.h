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
		std::string shaderPath = "assets/shaders/3D/default.shader";
		std::string cubeShaderPath = "assets/shaders/3D/flat.shader";
		std::vector<int> cubeLayout  = { 3, 2, 3 };
		std::vector<int> floorLayout = { 3, 3 };


		// float vertices[8 * 8] = {
		// // Positions (x,y,z)  Texture coords     Color
		// -0.5f, -0.5f,  0.5f,    0.0f, 1.0f,    1.0f, 1.0f, 1.0f,
		//  0.5f, -0.5f,  0.5f,    1.0f, 0.0f,    0.2f, 0.5f, 0.0f,
		// -0.5f,  0.5f,  0.5f,    1.0f, 1.0f,    1.0f, 0.0f, 1.0f,
		//  0.5f,  0.5f,  0.5f,    1.0f, 1.0f,    0.3f, 0.5f, 0.0f,
		// -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,    0.0f, 1.0f, 0.0f,
		//  0.5f, -0.5f, -0.5f,    0.0f, 1.0f,    0.0f, 0.5f, 0.5f,
		// -0.5f,  0.5f, -0.5f,    1.0f, 1.0f,    0.7f, 0.0f, 1.0f,
		//  0.5f,  0.5f, -0.5f,    0.0f, 0.0f,    1.0f, 0.5f, 0.0f
		// };
		// unsigned int indices[6 * 6] = {
		// //Top
		// 2, 6, 7,
		// 2, 3, 7,
		// //Bottom
		// 0, 4, 5,
		// 0, 1, 5,
		// //Left
		// 0, 2, 6,
		// 0, 4, 6,
		// //Right
		// 1, 3, 7,
		// 1, 5, 7,
		// //Front
		// 0, 2, 3,
		// 0, 1, 3,
		// //Back
		// 4, 6, 7,
		// 4, 5, 7
	// };

	};
}
