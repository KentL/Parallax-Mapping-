#version 150

// Scene info
uniform mat4 WorldViewProj;
uniform mat4 World;
uniform mat3 WorldIT;

// Attributes
in vec4 a_position;
in vec2 a_uv1;
in vec3 a_normal;
in vec3 a_tangent;

// Varyings
out vec3 v_normal;
out vec3 v_tangent;
out vec4 v_pos;
out vec2 v_uv1;

void main()
{
    gl_Position = WorldViewProj * a_position;
	vec3 n = WorldIT * a_normal;

	// Output
    v_normal = n;

	vec4 t = World * vec4(a_tangent.xyz,1.0);
	v_tangent = t.xyz;

	v_pos = World * a_position;

	v_uv1 = a_uv1;
}


