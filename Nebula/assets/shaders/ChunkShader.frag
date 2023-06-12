#version 330 core

out vec4 FragColor;

//uniform vec3 objectColour;
in vec4 temp;
uniform usamplerBuffer blockPositions;
uniform usamplerBuffer u_BlockData;
void main() {
	FragColor = temp.z + texelFetch(blockPositions, 0) + texelFetch(u_BlockData, 2);
}
