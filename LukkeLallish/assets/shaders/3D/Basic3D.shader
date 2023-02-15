#shader vertex
#version 330 core

layout(location = 0) in vec3 pos;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0f);
}


#shader fragment
#version 330 core

out vec4 color;

uniform vec4 u_Color;

void main()
{
    color = u_Color;
}
