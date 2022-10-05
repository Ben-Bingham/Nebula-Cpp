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

uniform sampler2D offsetTexture;

void main() {
	ivec2 texSize = textureSize(offsetTexture, 0);
	int pixelX = gl_InstanceID % texSize.x;
	int pixelY = gl_InstanceID / texSize.x;

	vec3 offset = texture(offsetTexture, ivec2(pixelX, pixelY)).rgb;

	normal = normalize(transpose(inverse(mat3(model))) * inputNormal);

	fragmentPosition = vec3(model * vec4(inputPositon + offset, 1.0));

	textureCordinates = inputTextureCords;

	gl_Position = projection * view * model * vec4(inputPositon + offset, 1.0);
}