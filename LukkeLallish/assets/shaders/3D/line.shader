#shader vertex
#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 Color;

uniform mat4 u_ViewProj;

out vec2 v_TexCoord; 
out vec4 v_Color;

void main()
{
	vec4 position = u_ViewProj * vec4(pos, 1.0);
    gl_Position = position;

    v_Color = Color;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_Color;

void main()
{
    // color = v_Color;
    color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}