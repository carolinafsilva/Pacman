#version 330 core
in vec4 TexCoords;
out vec4 FragColor;

uniform sampler2D image;
uniform vec3 spriteColor;

void main()
{
    vec4 texColor = vec4(spriteColor, 1.0) * texture(image, TexCoords.xy);
    if(texColor.a < 0.1)
        discard;
    FragColor = texColor;
}
