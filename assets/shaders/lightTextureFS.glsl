#version 410

out vec4 FragColor;

struct DirectionalLight
{
	vec3 lightDirection;
	vec4 ambientColour;
	vec4 diffuseColour;
	vec4 specularColour;
};

uniform DirectionalLight directionLight;

in vec3 vertexNormalOut;
in vec3 cameraDirectionOut;
in vec2 vertexTextureCoordsOut;

uniform vec4 ambientMaterialColour=vec4(0.5f,0.0f,0.0f,1.0f);
uniform float specularPower=25.0f;

uniform sampler2D diffuseSampler;
uniform sampler2D specularSampler;

void main()
{
	vec3 lightDir=normalize(-directionLight.lightDirection);
	float diffuseTerm = max(dot(vertexNormalOut, lightDir),0.0f);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDir);
	float specularTerm = pow(max(dot(vertexNormalOut, halfWayVec),0.0f), specularPower);
	
	vec4 diffuseTextureColour = texture(diffuseSampler, vertexTextureCoordsOut);
	vec4 specularTextureColour = texture (specularSampler, vertexTextureCoordsOut);
	
	

	FragColor = (ambientMaterialColour*directionLight.ambientColour) + (diffuseTextureColour*directionLight.diffuseColour *diffuseTerm) + (specularTextureColour*directionLight.specularColour*specularTerm);
}
