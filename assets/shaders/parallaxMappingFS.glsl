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

uniform float bias = 0.03;
uniform float scale = 0.015;
uniform sampler2D heightMap;

void main()
{
	float height = texture(heightMap, vertexTextureCoordsOut).r;
	
	//vec2 correctedTexCoord = vertexTextureCoordsOut;
	
	vec2 correctedTexCoord = scale*vertexTextureCoordsOut.xy*height-bias;
	
	correctedTexCoord = vertexTextureCoordsOut - correctedTexCoord;

	vec3 bumpNormals = 2.0 * texture (normalSampler ,correctedTexCoord).rgb - 1.0;
	
	bumpNormals = normalize(bumpNormals);
	
	vec3 lightDir=normalize(-directionLight.lightDirection);
	float diffuseTerm = dot(bumpNormals, lightDir);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDir);
	float specularTerm = pow(dot(bumpNormals, halfWayVec), specularPower);
	
	vec4 diffuseTextureColour = texture(diffuseSampler, correctedTexCoord);
	vec4 specularTextureColour = texture (specularSampler, correctedTexCoord);
	
	//FragColor = vec4 (bumpNormals, 1.0f);

	FragColor = (ambientMaterialColour*directionLight.ambientColour) + (diffuseTextureColour*directionLight.diffuseColour *diffuseTerm) + (specularTextureColour*directionLight.specularColour*specularTerm);
}
