#shader vertex
#version 330 core

layout(location = 0) in vec3 pos;

uniform mat4 u_ViewProj;

out vec2 v_TexCoord; 
out vec4 v_Color;

void main()
{
	vec4 position = u_ViewProj * vec4(pos, 1.0);
    gl_Position = position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

void main()
{
    color = vec4(1.0f, 0.0f, 1.0f, 1.0f);
}