#version 150
#define BUMP	1

// Scene info
uniform mat4 WorldViewProj;
uniform mat4 World;
uniform mat3 WorldIT;
uniform vec3 ViewDir;

// Light Info
uniform vec4 LightAmbient;
uniform vec4 LightSpecular;
uniform vec4 LightDiffuse;
uniform vec3 LightPos;
uniform vec3 LightAttenuation;
uniform float LightRange;

// Material info
uniform vec4 MatAmbient;
uniform vec4 MatSpecular;
uniform vec4 MatDiffuse;

// Texture(s)
uniform sampler2D texture;
uniform sampler2D nmap;

// Varyings
in vec4 v_pos;
in vec3 v_normal;
in vec3 v_tangent;
in vec2 v_uv1;

out vec4 PixelColor;

#if BUMP
vec3 TangentToWorldSpace(vec3 normalMapSample, vec3 normal_world, vec3 tangent_world)
{
	vec3 nT = 2.0 * normalMapSample - 1.0;

	vec3 N = normal_world;
	vec3 T = normalize( tangent_world - dot(tangent_world, N) * N);
	vec3 B = cross(N, T);

	mat3 TBN = mat3(T,B,N);

	vec3 bumpNormal = TBN * nT;
	return bumpNormal;
}
#endif

void main()
{
#if BUMP
	vec3 face_normal = normalize( v_normal );
	vec3 normalMapSample = texture(nmap, v_uv1).rgb;
	vec3 n = TangentToWorldSpace( normalMapSample, face_normal, v_tangent );
#else
	vec3 n = normalize( v_normal );
#endif

	vec3 lightDir = LightPos - v_pos.xyz;
	float distance = length(lightDir);

	if( distance > LightRange )
	{
		PixelColor = vec4(1,0,0,1);
	}
	else
	{
		// normalize it
		lightDir /= distance;

		// Ambient
		vec4 ambient = MatAmbient * LightAmbient;

		// Diffuse
		vec4 diffuse = MatDiffuse * LightDiffuse * max(0.0,dot(n, lightDir));

		// Specular
		vec3 R = reflect(-lightDir,n);
		float specFactor = pow(max(dot(R, ViewDir), 0.0), MatSpecular.w);
		vec4 specular = specFactor * MatSpecular * LightSpecular;

		// Combine the components
		vec4 light = clamp(ambient + diffuse + specular, 0, 1);

		// Attenuate the light
		float att = 1.0 / dot(LightAttenuation, vec3(1.0, distance, distance*distance));
		light *= att;

		PixelColor = light * texture(texture, v_uv1);
	}
}


