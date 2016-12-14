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


uniform vec4 ambientMaterialColour;
uniform float specularPower;

uniform sampler2D diffuseSampler;
uniform sampler2D specularSampler;
uniform sampler2D normalSampler;

void main()
{
	vec3 bumpNormals = 2.0 * texture (normalSampler ,vertexTextureCoordsOut ).xyz - 1.0;
	
	bumpNormals = normalize(bumpNormals);
	
	vec3 lightDir=normalize(-directionLight.lightDirection);
	
	float diffuseTerm = max(dot(bumpNormals, lightDir),0.0f);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDir);
	float specularTerm = pow(max(dot(bumpNormals, halfWayVec),0.0f), specularPower);
	
	vec4 diffuseTextureColour = texture(diffuseSampler, vertexTextureCoordsOut);
	vec4 specularTextureColour = texture (specularSampler, vertexTextureCoordsOut);
	
	vec4 ambientColour = ambientMaterialColour*directionLight.ambientColour;
	vec4 diffuseColour = diffuseTextureColour*directionLight.diffuseColour *diffuseTerm;
	vec4 specularColour = specularTextureColour*directionLight.specularColour*specularTerm;
	//ambientColour.a=ambientMaterialColour.a;
	//diffuseColour.a=diffuseTextureColour.a;
	//specularColour.a=specularTextureColour.a;
	
	FragColor = (ambientColour + diffuseColour+ specularColour);
}
