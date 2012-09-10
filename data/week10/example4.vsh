#version 150
uniform mat4 WorldViewProj;
uniform mat3 WorldIT;
uniform vec3 Light1Dir;
uniform vec4 Light1Color;
in vec4 a_position;
in vec3 a_normal;
in vec2 a_uv1;
out vec4 v_color;
out vec3 v_normal;
out vec2 v_uv1;

void main()
{
    gl_Position = WorldViewProj * a_position;
	vec3 n = WorldIT * a_normal;
	v_color = Light1Color * dot(n, Light1Dir);
	v_normal = n;
	v_uv1 = a_uv1;
}
