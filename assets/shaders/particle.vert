#version 330 core
layout (location = 0) in vec4 vertex;

out vec2 TexCoords;
out float ColorAlpha;

uniform vec2[500] offset;
uniform float[500] alpha;
uniform mat4 projection;

void main()
{
    ColorAlpha = alpha[gl_InstanceID];
    TexCoords = vertex.zw;
    gl_Position = projection * vec4((vertex.xy * 20.0) + offset[gl_InstanceID], 0.0, 1.0);
}