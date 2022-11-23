#version 430

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

void main() {
	vec4 center = gl_in[0].gl_Position;
	
	gl_Position = center + vec4(1, 1, 0, 0);
	EmitVertex();

	gl_Position = center + vec4(1, -1, 0, 0);
	EmitVertex();

	gl_Position = center + vec4(-1, 1, 0, 0);
	EmitVertex();

	gl_Position = center + vec4(-1, -1, 0, 0);
	EmitVertex();

	EndPrimitive();
}