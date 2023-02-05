#shader vertex
#version 330 core

// Positions/Coordinates
layout(location = 0) in vec3 aPos;
// Colors
layout(location = 1) in vec3 aColor;
// Texture Coordinates
layout(location = 2) in vec2 aTex;


// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;

uniform float scale;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	// Outputs the positions/coordinates of all vertices
	gl_Position = proj * view * model * vec4(aPos, 1.0);
	// Assigns the colors from the Vertex Data to "color"
	// color = aColor;
	color = vec3(1.0f, 0.50f, 1.0f, 1.0f);
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;
}


#shader fragment
#version 330 core

layout(location = 0) out vec3 aPos;
// Colors
layout(location = 1) out vec3 aColor;

// Outputs colors in RGBA
out vec4 FragColor;
// Inputs the color from the Vertex Shader
in vec3 color;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;

// Gets the Texture Unit from the main function


void main()
{
	FragColor = aColor;
}