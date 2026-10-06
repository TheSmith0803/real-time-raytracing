#version 330 core

out vec4 FragColor;

in vec3 position;
in float radius;

struct Ray {
	vec3 origin;
	vec3 dir;
};

uniform Ray r;

void main() {
	
	
	FragColor = 
}