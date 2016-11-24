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
in vec3 lightDirectionOut;
in mat3 tangentMatrix;


uniform vec4 ambientMaterialColour=vec4(0.5f,0.0f,0.0f,1.0f);
uniform float specularPower=25.0f;

uniform sampler2D diffuseSampler;
uniform sampler2D specularSampler;
uniform sampler2D normalSampler;

void main()
{
	vec3 bumpNormals = 2.0 * texture (normalSampler ,vertexTextureCoordsOut ).xyz - 1.0;
	
	bumpNormals = normalize(bumpNormals);
	
	vec3 lightDir=normalize(-directionLight.lightDirection);
	float diffuseTerm = dot(bumpNormals, lightDir);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDir);
	float specularTerm = pow(dot(bumpNormals, halfWayVec), specularPower);
	
	vec4 diffuseTextureColour = texture(diffuseSampler, vertexTextureCoordsOut);
	vec4 specularTextureColour = texture (specularSampler, vertexTextureCoordsOut);
	
	

	FragColor = (ambientMaterialColour*directionLight.ambientColour) + (diffuseTextureColour*directionLight.diffuseColour *diffuseTerm) + (specularTextureColour*directionLight.specularColour*specularTerm);
}
