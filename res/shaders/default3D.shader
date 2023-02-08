#shader vertex
#version 330 core

layout(location = 0) in vec4 pos;
layout(location = 1) in vec2 texCoord;
// Output texture coordinates from vertex shader -> fragment shader
out vec2 v_TexCoord; // varying texture coordinate
uniform mat4 camMatrix;

void main()
{
	// gl_Position = pos;
	gl_Position = camMatrix * pos;
	v_TexCoord = texCoord;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec2 v_TexCoord;

// uniform mat4 camMatrix;
uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	// color = u_Color;
	color = texColor;
}