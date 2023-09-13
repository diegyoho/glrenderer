#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoords;

uniform mat4 MVP;

out vec2 TexCoords;

void main()
{
    TexCoords = texCoords;
    gl_Position = MVP * position;
}

#shader fragment
#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform vec4 color;
uniform sampler2D textureSampler;

void main()
{
    FragColor = texture(textureSampler, TexCoords) * color;
}