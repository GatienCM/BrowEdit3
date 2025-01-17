#version 420

uniform sampler2D s_texture;
uniform sampler2D s_lighting;
uniform sampler2D s_tileColor;

uniform vec3 lightDiffuse;
uniform vec3 lightAmbient;
uniform vec3 lightDirection;
uniform float lightIntensity;
uniform float lightToggle = 1.0f;
uniform float colorToggle = 1.0f;
uniform float lightColorToggle = 1.0f;
uniform float shadowMapToggle = 1.0f;

in vec2 texCoord;
in vec2 texCoord2;
in vec2 tileColorCoord;
in vec3 normal;

out vec4 fragColor;
//out vec4 fragSelection;

void main()
{
	vec4 texture = vec4(1,1,1,1);
	
	texture *= texture2D(s_texture, texCoord);
	texture *= max(texture2D(s_tileColor, tileColorCoord), colorToggle);
	texture *= max(texture2D(s_lighting, texCoord2).a, shadowMapToggle);


	texture.rgb *= max((abs(dot(normal, lightDirection)) * lightDiffuse + lightIntensity * lightAmbient), lightToggle);
	texture += clamp(vec4(texture2D(s_lighting, texCoord2).rgb,1.0), 0.0, 1.0) * lightColorToggle;


	//gl_FragData[0] = texture;
	//gl_FragData[1] = vec4(0,0,0,0);
	fragColor = texture;
}