#shader vertex
#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 Color;

uniform mat4 u_ViewProj;
uniform mat4 u_Model;
out vec4 v_Color;

void main()
{
	gl_Position = u_ViewProj * u_Model * vec4(pos, 1.0);
    v_Color = Color;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;

void main()
{
    color = v_Color;
}
