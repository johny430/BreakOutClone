#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D scene;
uniform vec2  offsets[9];
uniform float  blur_kernel[9];

uniform bool shake;

void main()
{
    color = vec4(0.0f);
    if(shake)
    {
        for(int i = 0; i < 9; i++)
        {
            color += vec4(vec3(texture(scene, TexCoords.st + offsets[i])) * blur_kernel[i], 0.0f);
        }
        color.a = 1.0f;
    }
    else
    {
        color =  texture(scene, TexCoords);
    }
}