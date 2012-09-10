#version 150
uniform mat4 WorldViewProj;
uniform mat3 WorldIT;
uniform vec3 Light1Dir;
uniform vec4 Light1Color;
uniform vec3 ViewDir;
uniform float Shininess;
uniform vec3 SpecularColor;
in vec4 a_position;
in vec3 a_normal;
in vec2 a_uv1;
out vec4 v_color;
out vec2 v_uv1;

void main()
{
    gl_Position = WorldViewProj * a_position;
	vec3 n = WorldIT * a_normal;
	vec3 l = Light1Color.rgb * dot(n, Light1Dir);
	vec3 s = SpecularColor * pow(max(0.0,dot(reflect(-Light1Dir,n),ViewDir)),Shininess);

	v_color = vec4( l + s, 1.0 );
	v_uv1 = a_uv1;
}
