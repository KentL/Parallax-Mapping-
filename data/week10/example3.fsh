#version 150
uniform sampler2D texture;

in vec4 v_color;
in vec2 v_uv1;
out vec4 PixelColor;

void main()
{
    PixelColor = texture(texture, v_uv1) * v_color;
}


