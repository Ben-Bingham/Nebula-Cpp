#version 330 core

layout (location = 0) in vec3 inputPositon;
layout (location = 1) in vec3 inputNormal;
layout (location = 2) in vec2 inputTextureCords;

out vec3 normal;
out vec3 fragmentPosition;
out vec2 textureCordinates;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform samplerBuffer offsetBuffer;

out vec3 test;

void main() {
	vec3 offset = texelFetch(offsetBuffer, gl_InstanceID).rgb;

	normal = normalize(transpose(inverse(mat3(model))) * inputNormal);

	fragmentPosition = vec3(model * vec4(inputPositon + offset, 1.0));

	textureCordinates = inputTextureCords;

	test = offset / 255;

	gl_Position = projection * view * model * vec4(inputPositon + offset, 1.0);
}