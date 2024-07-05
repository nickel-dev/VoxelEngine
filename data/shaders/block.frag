#version 460 core

uniform sampler2D uTexture;

in vec2 texCoord;
in float normal;

out vec4 fragColor;

void main()
{
    fragColor = texture(uTexture, texCoord) * vec4(0.16 * (normal + 1));
}