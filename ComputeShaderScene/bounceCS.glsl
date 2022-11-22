#version 430
#extension GL_ARB_compute_shader : enable
#extension GL_ARB_shader_storage_buffer_object : enable

layout(std430, binding = 0) buffer positionBuffer
{
	vec4 position[];
};

layout(std430, binding = 1) buffer velocityBuffer
{
	vec4 velocity[];
};

uniform float dt;

const vec4 g = vec4(0.0f, -10.0f, 0.0f, 1.0f);

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

void main()
{
	int i = int(gl_WorkGroupID.x);
	vec3 v0 = velocity[i].xyz;
	vec3 v1 = v0 + g.xyz * dt;

	vec3 p0 = position[i].xyz;
	vec3 p1 = p0 + v1 * dt;

	if (p1.y < 0.0f)
	{
		p1.y = p0.y;
		v1 = v0;
		v1.y = -v1.y;
	}

	position[i] = vec4(p1, 1);
	velocity[i] = vec4(v1, 1);
}