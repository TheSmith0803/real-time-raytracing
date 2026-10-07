#version 330 core

out vec4 FragColor;
in vec2 uv;

uniform vec3 cam_center;
uniform vec3 cam_front;

uniform float ar;
uniform int w;
uniform int h;

const float focal_length = 1.0f;

struct Sphere {
	vec3 center;
	float radius;
};

struct Ray {
	vec3 origin;
	vec3 dir;
};

vec3 at(Ray ray, float t) {
	return ray.origin + (ray.dir*t);
}

void main() {
	vec3 cur_pix = vec3(w * uv.x, h * uv.y, -focal_length);
	
	//construct a ray to cast into the scene
	Ray ray;
	ray.origin = cam_center;
	ray.dir = cur_pix;



	float rg = min(1.0f - (uv.y * 0.8f), 0.6f);	

	FragColor = vec4(rg, rg, 1.0f, 1.0f);
}