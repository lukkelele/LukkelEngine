#shader vertex
#version 330 core

layout(location = 0) in vec3 pos;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = proj * view * model * vec4(pos, 1.0f);
}


#shader fragment
#version 330 core

out vec4 color;

// uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_texCoord);
    // color = u_Color; 
    color = texColor; 

}
