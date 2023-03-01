#pragma once

namespace LukkelEngine {

	namespace WorldObject {

		struct Cube
		{
			Cube() = default;

			float CUBE_VERTICES[24] = {
				// Positions (x, y, z)
				-0.5f, -0.5f,  0.5f, // 0
				 0.5f, -0.5f,  0.5f, // 1
				-0.5f,  0.5f,  0.5f, // 2
				 0.5f,  0.5f,  0.5f, // 3
				-0.5f, -0.5f, -0.5f, // 4
				 0.5f, -0.5f, -0.5f, // 5
				-0.5f,  0.5f, -0.5f, // 6
				 0.5f,  0.5f, -0.5f, // 7
			};

			float CUBE_VERTICES_COLOR[56] = {
				// Positions (x,y,z)     Color
				-0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f, 0.7,
				 0.5f, -0.5f,  0.5f,   0.2f, 0.5f, 0.0f, 0.7,
				-0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f, 0.7,
				 0.5f,  0.5f,  0.5f,   0.3f, 0.5f, 0.0f, 0.7,
				-0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f, 0.7,
				 0.5f, -0.5f, -0.5f,   0.0f, 0.5f, 0.5f, 0.7,
				-0.5f,  0.5f, -0.5f,   0.7f, 0.0f, 1.0f, 0.7,
				 0.5f,  0.5f, -0.5f,   1.0f, 0.5f, 0.0f, 0.7
			};

			float CUBE_VERTICES_TEXTURES[40] = {
				// Positions (x,y,z)  Texture coords
				-0.5f, -0.5f,  0.5f,    0.0f, 1.0f,
				 0.5f, -0.5f,  0.5f,    1.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,    1.0f, 1.0f,
				 0.5f,  0.5f,  0.5f,    1.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
				-0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
				 0.5f,  0.5f, -0.5f,    0.0f, 0.0f,
			};

			float CUBE_VERTICES_TEXTURES_COLOR[81] = {
				// Positions (x,y,z)  Texture coords     Color
				-0.5f, -0.5f,  0.5f,    0.0f, 1.0f,    1.0f, 1.0f, 1.0f, 0.7,
				 0.5f, -0.5f,  0.5f,    1.0f, 0.0f,    0.2f, 0.5f, 0.0f, 0.7,
				-0.5f,  0.5f,  0.5f,    1.0f, 1.0f,    1.0f, 0.0f, 1.0f, 0.7,
				 0.5f,  0.5f,  0.5f,    1.0f, 1.0f,    0.3f, 0.5f, 0.0f, 0.7,
				-0.5f, -0.5f, -0.5f,    0.0f, 1.0f,    0.0f, 1.0f, 0.0f, 0.7,
				 0.5f, -0.5f, -0.5f,    0.0f, 1.0f,    0.0f, 0.5f, 0.5f, 0.7,
				-0.5f,  0.5f, -0.5f,    1.0f, 1.0f,    0.7f, 0.0f, 1.0f, 0.7,
				 0.5f,  0.5f, -0.5f,    0.0f, 0.0f,    1.0f, 0.5f, 0.0f, 0.7
			};

			unsigned int CUBE_INDICES[36] = {
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

}