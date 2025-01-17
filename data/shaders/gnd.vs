#version 420

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texture;
layout (location = 2) in vec2 a_texture2;
layout (location = 3) in vec2 a_tileColorCoord;
layout (location = 4) in vec3 a_normal;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

out vec2 texCoord;
out vec2 texCoord2;
out vec2 tileColorCoord;
out vec3 normal;

void main()
{
	texCoord = a_texture;
	texCoord2 = a_texture2;
	tileColorCoord = a_tileColorCoord;
	normal = a_normal;
	gl_Position = projectionMatrix * modelViewMatrix * vec4(a_position,1);
}