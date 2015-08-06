#version 150
in vec4 v_color;
out vec4 PixelColor;
uniform float Color;

void main()
{
    PixelColor = v_color;
}
