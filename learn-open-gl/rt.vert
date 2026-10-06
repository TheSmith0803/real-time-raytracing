#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in float aRad;

out vec3 position;
out float radius

void main() {
	
	position = aPos;
	radius = aRad;

	gl_Position = vec4(1.0, 1.0, 1.0, 1.0);
}