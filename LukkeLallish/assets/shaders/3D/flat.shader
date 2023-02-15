#shader vertex
#version 330 core

layout(location = 0) in vec3 pos;

uniform mat4 u_ViewProjection;
uniform mat4 model;
// uniform mat4 u_Transform;

void main()
{
	// gl_Position = u_ViewProjection * u_Transform * vec4(pos, 1.0);
	gl_Position = u_ViewProjection * model * vec4(pos, 1.0);
	// gl_Position = u_ViewProjection * vec4(pos, 1.0);
	// gl_Position = vec4(pos, 1.0);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main()
{
	color = u_Color;
}