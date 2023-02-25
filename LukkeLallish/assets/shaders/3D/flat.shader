#shader vertex
#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 Color;

uniform mat4 u_ViewProj;
uniform mat4 u_Model;
out vec2 v_TexCoord; 
out vec4 v_Color;
// uniform mat4 u_Transform;

void main()
{
	gl_Position = u_ViewProj * u_Model * vec4(pos, 1.0);
    v_TexCoord = texCoord;
    v_Color = vec4(Color, 1.0f);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

// uniform vec4 u_Color;
// Texture
in vec2 v_TexCoord;
in vec4 v_Color; // if used, make sure renderer isn't drawing lines only
uniform sampler2D u_Texture;

void main()
{
    color = v_Color;
}