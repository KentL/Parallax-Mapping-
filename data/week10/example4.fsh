#version 150
uniform vec3 ViewDir;
uniform vec3 Light1Dir;
uniform float Shininess;
uniform vec3 SpecularColor;
uniform sampler2D texture;

in vec4 v_color;
in vec3 v_normal;
in vec2 v_uv1;
out vec4 PixelColor;

void main()
{
	vec3 n = normalize( v_normal );
	vec3 s = SpecularColor * pow(max(0.0,dot(reflect(-Light1Dir,n),ViewDir)), Shininess);

    PixelColor = texture(texture, v_uv1) * vec4( v_color.rgb + s, v_color.a);
}


