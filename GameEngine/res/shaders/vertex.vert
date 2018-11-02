#version 330 core

layout(location = 0) in vec4 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 MVP;

out vec3 fragNormal;
out vec2 fragTexCoord;

void main(){
	fragNormal = normal;
	fragTexCoord = texCoord;

	gl_Position = MVP * vertex;
}