#version 330 core

out vec4 FragColor;

//uniform vec3 objectColour;
in vec4 temp;

void main() {
	FragColor = temp;
}
