#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

out vec4 FragPosition;

void main()
{
    FragPosition = position;
    gl_Position = position;
}

#shader fragment
#version 330 core

in vec4 FragPosition;

out vec4 FragColor;

uniform vec4 Color;

void main()
{
    FragColor = Color;
}