#version 150
uniform mat4 WorldViewProj;
uniform mat3 WorldIT;
uniform vec3 LightDir;
uniform vec4 LightColor;
in vec4 a_position;
in vec3 a_normal;
out vec4 v_color;

void main()
{
    gl_Position = WorldViewProj * a_position;
	vec3 n = WorldIT * a_normal;
	v_color = LightColor * max(0, dot(n, LightDir));
}

