#version 330 core

layout (location = 0) in vec3 inputPositon;
layout (location = 1) in vec3 inputNormal;
layout (location = 2) in vec2 inputTextureCords;

uniform mat4 modelViewProjection;

uniform usamplerBuffer blockPositions;
uniform usamplerBuffer u_BlockData;

out vec4 temp;

void main() {
	vec4 offset = texelFetch(blockPositions, gl_InstanceID);
	
	float r = offset.x / 16.0;
	float g = offset.y / 256.0;
	float b = offset.z / 16.0 + texelFetch(u_BlockData, 0).x;

	temp = vec4(gl_InstanceID / (16 * 16 * 256), g, b, 1.0);

	gl_Position = modelViewProjection * vec4(inputPositon + vec3(offset.xyz), 1.0);
}