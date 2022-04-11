#version 330 core
in vec2 TexCoords;
in float ColorAlpha;
out vec4 color;

uniform sampler2D sprite;

void main()
{
	color = vec4(texture(sprite, TexCoords).rgb,ColorAlpha);
}