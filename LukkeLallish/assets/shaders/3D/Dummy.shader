#shader vertex
#version 330 core

layout(location = 0) in vec4 pos;
layout(location = 1) in vec3 color;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;

out vec3 out_color;

void main()
{
	gl_Position = projection * view * model * pos;
	out_color = color;
}

#shader fragment
#version 330 core

in vec3 out_color;
out vec4 color;

// Change color to vec4 instead
void main()
{
	color = vec4(out_color, 1.0f);
}
