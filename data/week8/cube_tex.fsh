#version 150
in vec2 v_uv1;

uniform sampler2D texture;
uniform float fade;

out vec4 PixelColor;

void main()
{
    PixelColor = texture(texture, v_uv1);
	PixelColor.a *= fade;
}
