#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D sprite;
uniform vec3 in_color;

void main()
{
    
    color = texture(sprite, TexCoords) * vec4(in_color,1.0f);
}