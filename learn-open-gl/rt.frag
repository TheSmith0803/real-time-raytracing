#version 330 core

out vec4 FragColor;
in vec2 uv;
in float ar;

struct Sphere {
	vec3 center;
	float radius;
};

struct Ray {
	vec3 origin;
	vec3 dir;
};

Ray ray;
Sphere sphere;



void main() {
	ray.origin = vec3(0.0f);

	sphere.center = vec3(0.5,0.5, -0.5f);
	sphere.radius = 0.2;

	vec3 p = vec3(uv, 0.0f) - sphere.center;
	p.x *= ar;

	float dist = length(p);

	float rg = min(1.0f - (uv.y * 0.8f), 0.6f);	

	if (dist < sphere.radius)
		FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	else
		FragColor = vec4(rg, rg, 1.0f, 1.0f);
}