#version 330 core

in vec3 fragNormal;
in vec3 fragTexCoord;

out vec4 outFragColor;

void main(){
	outFragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}