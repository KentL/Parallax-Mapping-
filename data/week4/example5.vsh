#version 150
uniform mat4 WorldViewProj;
uniform vec4 Color;
in vec4 a_position;
in vec4 a_color;
out vec4 v_color;
uniform float time;
void main()
{
    gl_Position = WorldViewProj * a_position;
	
	v_color = (a_color)+Color;
}
