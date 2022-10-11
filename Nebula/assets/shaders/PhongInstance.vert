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

uniform isamplerBuffer offsetBuffer;

uniform int texturesPerSide;

out vec3 test;

void main() {
	unsigned ivec4 instanceInfo = unsigned ivec4(texelFetch(offsetBuffer, gl_InstanceID).rgba);

	unsigned int pos = instanceInfo.a;

	unsigned ivec3 offset;
	offset.z = (pos >> 8) & 255u;
	offset.y = (pos >> 16) & 255u;
	offset.x = (pos >> 24) & 255u;

	normal = normalize(transpose(inverse(mat3(model))) * inputNormal);

	fragmentPosition = vec3(model * vec4(inputPositon + offset, 1.0));

	int textureIndex = 0;

	if (gl_VertexID < 4) {		// Pos Z
		textureIndex = int((instanceInfo.z >> 16) & 0xFFFFu);
	}
	else if (gl_VertexID < 8) { // Pos X
		textureIndex = int((instanceInfo.x >> 16) & 0xFFFFu);
	}
	else if (gl_VertexID < 12) { // Neg X
		textureIndex = int(instanceInfo.x & 0xFFFFu);
	}
	else if (gl_VertexID < 16) { // Pos Y
		textureIndex = int((instanceInfo.y >> 16) & 0xFFFFu);
	}
	else if (gl_VertexID < 20) { // Neg Z
		textureIndex = int(instanceInfo.z & 0xFFFFu);
	}
	else if (gl_VertexID < 24) { // Neg Y
		textureIndex = int(instanceInfo.y & 0xFFFFu);
	}

	vec2 texCords;

	texCords = inputTextureCords / texturesPerSide;
	int x = textureIndex % texturesPerSide;
	int y = textureIndex / texturesPerSide;
	float imageWorth = 1.0 / texturesPerSide;
	
	texCords.x += imageWorth * x;
	texCords.y += imageWorth * y;
	
	textureCordinates = texCords;

	gl_Position = projection * view * model * vec4(inputPositon + offset, 1.0);
}