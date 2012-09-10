#version 150
uniform mat4 WorldViewProj;
uniform mat3 WorldIT;
uniform vec3 Light1Dir;
uniform vec4 Light1Color;
uniform vec3 Light2Dir;
uniform vec4 Light2Color;
in vec4 a_position;
in vec3 a_normal;
out vec4 v_color;

void main()
{
    gl_Position = WorldViewProj * a_position;
	vec3 n = WorldIT * a_normal;
	vec3 l1 = Light1Color.rgb * max(0, dot(n, Light1Dir));
	vec3 l2 = Light2Color.rgb * max(0, dot(n, Light2Dir));
	v_color = vec4(l1+l2, 1);
}


