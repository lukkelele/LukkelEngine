#include "LKpch.h"
#include "LukkelEngine/Physics/Collision.h"
#include "LukkelEngine/Renderer/Camera.h"
#include "LukkelEngine/Input/Mouse.h"
#include "LukkelEngine/Scene/Entity.h"


namespace LukkelEngine {

	void CollisionDetector::Collision(btPersistentManifold* manifold)
	{

	}

	void CollisionDetector::Separation(btPersistentManifold* manifold)
	{

	}

	std::pair<glm::vec3, glm::vec3> CollisionDetector::Raycast(const Camera& camera)
	{
		auto [mouseX, mouseY] = Mouse::GetMousePosition();
		auto& cam = camera;
		auto screenWidth = cam.GetScreenWidth();
		auto screenHeight = cam.GetScreenHeight();
		auto projection = cam.GetProjection();
		auto view = cam.GetView();

		// Lock the ray to the middle of the screen, need to fix the GLFW cursor pos 
		mouseX = screenWidth / 2;
		mouseY = screenHeight / 2;

		glm::vec4 rayStart_NDC(
			((float)mouseX/(float)screenWidth  - 0.5f) * 2.0f, // [0,  width] -> [-1,1]
			((float)mouseY/(float)screenHeight - 0.5f) * 2.0f, // [0, height] -> [-1,1]
		   -1.0, // The near plane maps to Z=-1
			1.0f
		);
		glm::vec4 rayEnd_NDC(
			((float)mouseX/(float)screenWidth  - 0.5f) * 2.0f, // * -1 (?)
			((float)mouseY/(float)screenHeight - 0.5f) * 2.0f,
			0.0,
			-1.0f
		);

		glm::mat4 invViewProjection = glm::inverse(projection * view);
		glm::vec4 rayStart_world = invViewProjection * rayStart_NDC;
		glm::vec4 rayEnd_world   = invViewProjection * rayEnd_NDC  ; 
		rayStart_world /= rayStart_world.w;
		rayEnd_world   /= rayEnd_world.w;

		glm::vec3 rayDirection_world(rayEnd_world - rayStart_world);
		rayDirection_world = glm::normalize(rayDirection_world);

		glm::vec3 rayPos = glm::vec3(rayStart_world);
		glm::vec3 rayDir = glm::normalize(rayDirection_world);

		return { rayPos, rayDir };
	}

}