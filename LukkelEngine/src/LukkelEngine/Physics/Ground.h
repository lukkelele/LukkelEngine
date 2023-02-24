#pragma once

#include "LukkelEngine/Scene/Entity.h"
#include "LukkelEngine/Physics/Box.h"

namespace LukkelEngine {

	class Ground : public Entity
	{
	public:
		Ground();
		~Ground() = default;

	private:
		float vertices[8 * 8] = {
		// Positions		 Texture coords 
		-0.0f,  0.0f, 0.0f, 0.0f, 1.0f, 
		 100.0f, -100.0f,  0.5f,   1.0f, 0.0f,   
		-0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   
		 0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   
		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   
		 0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   
		 0.5f,  0.5f, -0.5f,   0.0f, 0.0f,   
		};

		// -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 
		//  0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   
		// -0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   
		//  0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   
		// -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   
		//  0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   
		// -0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   
		//  0.5f,  0.5f, -0.5f,   0.0f, 0.0f,   

		float vertices_color[8 * 8] = {
		// Positions		 Texture coords    Color
		-0.5f, -0.5f,  0.5f,   0.0f, 1.0f,    1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,   1.0f, 0.0f,    0.2f, 0.5f, 0.0f,
		-0.5f,  0.5f,  0.5f,   1.0f, 1.0f,    1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 1.0f,    0.3f, 0.5f, 0.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f,    0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,   0.0f, 1.0f,    0.0f, 0.5f, 0.5f,
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f,    0.7f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,   0.0f, 0.0f,    1.0f, 0.5f, 0.0f
		};
		
		unsigned int indices[6 * 6] = {
			//Top
			2, 6, 7,
			2, 3, 7,
			//Bottom
			0, 4, 5,
			0, 1, 5,
			//Left
			0, 2, 6,
			0, 4, 6,
			//Right
			1, 3, 7,
			1, 5, 7,
			//Front
			0, 2, 3,
			0, 1, 3,
			//Back
			4, 6, 7,
			4, 5, 7
		};
	};
}
