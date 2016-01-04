#version 330

in vec2 texCoordOut;

uniform sampler2D tex;

out vec4 color;

void main(void)
{
    color = texture(tex, vec2(texCoordOut.x, 1-texCoordOut.y));
}

