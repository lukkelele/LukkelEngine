#shader vertex
#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 Color;

uniform mat4 u_ViewProjection;
uniform mat4 model;
out vec2 v_texCoord; 
out vec4 v_Color;
// uniform mat4 u_Transform;

void main()
{
	gl_Position = u_ViewProjection * model * vec4(pos, 1.0);
    v_texCoord = texCoord;
    v_Color = vec4(Color, 1.0f);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

// uniform vec4 u_Color;
// Texture
in vec2 v_texCoord;
in vec4 v_Color; // if used, make sure renderer isn't drawing lines only
uniform sampler2D u_Texture;

void main()
{
    // vec4 texColor = texture(u_Texture, v_texCoord);
    // color = texColor; 
    color = v_Color;
}