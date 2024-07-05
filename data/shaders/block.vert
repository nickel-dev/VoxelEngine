#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 uModel;
uniform mat4 uProjection;
uniform mat4 uView;

out vec2 texCoord;
out float normal;

void main()
{
    gl_Position =  uProjection * uView * uModel * vec4(aPos, 1.0);

    texCoord = aTexCoord;
    /*switch (int(aNormal))
    {
    case 0:
    texCoord = vec2(0.5, 1.0);
    break;

    case 1:
    texCoord = vec2(1.0, 0.0);
    break;

    case 2:
    texCoord = vec2(1.0, 0.8);
    break;

    case 3:
    texCoord = vec2(0.0, 1.0);
    break;

    case 4:
    texCoord = vec2(1.0, 0.5);
    break;

    case 5:
    texCoord = vec2(0.5, 1.0);
    break;

    default:
    break;
    };*/

    normal = aNormal;
}