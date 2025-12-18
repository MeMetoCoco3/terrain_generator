#version 330 core
layout(location = 0) in vec3 aPos;

out float z;

uniform mat4 model_mat;
uniform mat4 view_mat;
uniform mat4 proj_mat;
uniform sampler2D perlin_noise;
void main() 
{
	vec2 UV = vec2(aPos.x, aPos.y);
	vec4 PerlinPos = vec4(aPos, 1.0f);
	PerlinPos.z = texture(perlin_noise, UV).x;
	vec4 world_pos = proj_mat * view_mat * model_mat * PerlinPos;

	z = PerlinPos.z;
	gl_Position = world_pos;

}
