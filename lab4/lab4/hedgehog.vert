#version 330

in vec3 coord;
in vec2 texCoordIn;

uniform mat4 modelMatrix;
uniform mat4 cameraMatrix;

out vec2 texCoordOut;

void main(void)
{
    gl_Position = cameraMatrix * modelMatrix * vec4(coord, 1.0);
    texCoordOut = vec2(texCoordIn.x, 1-texCoordIn.y);
}


