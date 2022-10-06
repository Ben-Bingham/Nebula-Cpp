#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

#define MAX_POINT_LIGHTS 16
#define MAX_DIRECTIONAL_LIGHTS 16

struct PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
    float linear;
    float quadratic;
};

struct DirectionalLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;

uniform PointLight[MAX_POINT_LIGHTS] pointLights;
uniform int numberOfPointLights;

uniform DirectionalLight[MAX_DIRECTIONAL_LIGHTS] directionalLights;
uniform int numberOfdirectionalLights;

out vec4 FragColor;

in vec3 normal;
in vec3 fragmentPosition;
in vec2 textureCordinates;

uniform vec3 cameraPosition;

vec3 calcPointLight(PointLight, vec3);
vec3 calcDirectionalLight(DirectionalLight, vec3);

void main() {
	vec3 viewDirection = normalize(cameraPosition - fragmentPosition);

	vec3 result = vec3(0.0, 0.0, 0.0);

	for (int i = 0; i < numberOfPointLights; i++) {
		result += calcPointLight(pointLights[i], viewDirection);
	}

	for (int i = 0; i < numberOfdirectionalLights; i++) {
		result += calcDirectionalLight(directionalLights[i], viewDirection);
	}

	FragColor = vec4(result, 1.0);
}

vec3 calcPointLight(PointLight pointLight, vec3 viewDirection) {
	// Ambient
	vec3 ambient = pointLight.ambient * texture(material.diffuse, textureCordinates).rgb;
	
	// Diffuse
	vec3 lightDirection = normalize(pointLight.position - fragmentPosition);
	float angleOfNormAndLightDir = max(dot(normal, lightDirection), 0.0);
	vec3 diffuse = pointLight.diffuse * angleOfNormAndLightDir * texture(material.diffuse, textureCordinates).rgb;

	// Specular
	vec3 halfwayDirection = normalize(lightDirection + viewDirection);
	float specularAmount = pow(max(dot(normal, halfwayDirection), 0.0), material.shininess);
	vec3 specular = pointLight.specular * (specularAmount * texture(material.specular, textureCordinates).rgb);

	// Attenuation
	float distanceBetweenLightAndFrag = length(pointLight.position - fragmentPosition);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distanceBetweenLightAndFrag + pointLight.quadratic * (distanceBetweenLightAndFrag * distanceBetweenLightAndFrag));    

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	// Total
	return ambient + diffuse + specular;
}

vec3 calcDirectionalLight(DirectionalLight directionalLight, vec3 viewDirection) {
	// Ambient
	vec3 ambient = directionalLight.ambient * texture(material.diffuse, textureCordinates).rgb;

	// Diffuse
	vec3 lightDirection = normalize(-directionalLight.direction);
	float angleOfNormAndLightDir = max(dot(normal, lightDirection), 0.0);
	vec3 diffuse = directionalLight.diffuse * angleOfNormAndLightDir * texture(material.diffuse, textureCordinates).rgb;

	// Specular
	vec3 halfwayDirection = normalize(lightDirection + viewDirection);
	float specularAmount = pow(max(dot(normal, halfwayDirection), 0.0), material.shininess);
	vec3 specular = directionalLight.specular * (specularAmount * texture(material.specular, textureCordinates).rgb);

	// Total
	return ambient + diffuse + specular;
}