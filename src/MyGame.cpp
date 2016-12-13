#include "MyGame.h"

const std::string ASSET_PATH = "assets";
const std::string SHADER_PATH = "/shaders";
const std::string TEXTURE_PATH = "/textures";
const std::string MODEL_PATH = "/models";

MyGame::MyGame()
{
	m_CameraPosition = vec3(0.0f, 0.0f, 10.0f);
	m_CameraFront = vec3(0.0f, 0.0f, -1.0f);
	m_CameraUp = vec3(0.0f, 1.0f, 0.0f);
	cameraSpeed = 1.0f;

	yaw = -90.0f;
	pitch = 0.0f;
	lastX = m_WindowWidth / 2;
	lastY = m_WindowHeight / 2;
	fov = radians(45.0f);

	deltaTime = 0.0f;
	lastFrame = 0.0f;


}

MyGame::~MyGame()
{

}

void MyGame::initScene()
{
	string modelPath = ASSET_PATH + MODEL_PATH + "/Earth.fbx";

	string modelTest = ASSET_PATH + MODEL_PATH + "/woodboard.fbx";

	string vsTextureFilename = ASSET_PATH + SHADER_PATH + "/lightTextureVS.glsl";
	string fsTextureFilename = ASSET_PATH + SHADER_PATH + "/lightTextureFS.glsl";
	string vsNormalFilename = ASSET_PATH + SHADER_PATH + "/normalMappingVS.glsl";
	string fsNormalFilename = ASSET_PATH + SHADER_PATH + "/normalMappingFS.glsl";
	string vsParallaxFilename = ASSET_PATH + SHADER_PATH + "/parallaxMappingVS.glsl";
	string fsParallaxFilename = ASSET_PATH + SHADER_PATH + "/parallaxMappingFS.glsl";

	string diffuseTexturePathEarth = ASSET_PATH + TEXTURE_PATH + "/earth_diff.png";
	string specularTexturePathEarth = ASSET_PATH + TEXTURE_PATH + "/earth_spec.png";
	string normalTexturePathEarth = ASSET_PATH + TEXTURE_PATH + "/earth_norm.png";
	string parallaxTexturePathEarth = ASSET_PATH + TEXTURE_PATH + "/earth_height.png";

	string diffuseTexturePathBricks = ASSET_PATH + TEXTURE_PATH + "/bricks_diff.jpg";
	string specularTexturePathBricks = ASSET_PATH + TEXTURE_PATH + "/bricks_spec.png";
	string normalTexturePathBricks = ASSET_PATH + TEXTURE_PATH + "/bricks_norm.png";
	string parallaxTexturePathBricks = ASSET_PATH + TEXTURE_PATH + "/bricks_height.png";

	string diffuseTexturePathBaord = ASSET_PATH + TEXTURE_PATH + "/boards_color.png";
	string specularTexturePathBoard = ASSET_PATH + TEXTURE_PATH + "/boards_spec.png";
	string normalTexturePathBoard = ASSET_PATH + TEXTURE_PATH + "/boards_normal.png";
	string parallaxTexturePathBoard = ASSET_PATH + TEXTURE_PATH + "/boards_height.png";


	m_TestGO=shared_ptr<GameObject>(loadModelFromFile(modelPath));
	m_TestGO->loadShaders(vsNormalFilename, fsNormalFilename);
	m_TestGO->loadDiffuseTexture(diffuseTexturePathBricks);
	m_TestGO->loadSpecularTexture(specularTexturePathBricks);
	m_TestGO->loadNormalTexture(normalTexturePathBricks);

	m_TestGO->setScale(vec3(0.5f, 0.5f, 0.5f));
	m_TestGO->setPosition(vec3(0.0f, 0.0f, 0.0f)); 

	/*m_TestGO = shared_ptr<GameObject>(loadModelFromFile(modelTest));
	m_TestGO->loadShaders(vsParallaxFilename, fsParallaxFilename);
	m_TestGO->loadDiffuseTexture(diffuseTexturePathBaord);
	m_TestGO->loadSpecularTexture(specularTexturePathBoard);
	m_TestGO->loadNormalTexture(normalTexturePathBoard);
	m_TestGO->loadHeightTexture(parallaxTexturePathBoard);

	m_TestGO->setScale(vec3(0.2f, 0.2f, 0.2f));
	m_TestGO->setPosition(vec3(0.0f, 0.0f, 0.0f));*/ //woodboard

	m_TestGO2 = shared_ptr<GameObject>(loadModelFromFile(modelPath));
	m_TestGO2->loadShaders(vsParallaxFilename, fsParallaxFilename);
	m_TestGO2->loadDiffuseTexture(diffuseTexturePathBricks);
	m_TestGO2->loadSpecularTexture(specularTexturePathBricks);
	m_TestGO2->loadNormalTexture(normalTexturePathBricks);
	m_TestGO2->loadHeightTexture(parallaxTexturePathBricks);

	m_TestGO2->setScale(vec3(0.5f, 0.5f, 0.5f));
	m_TestGO2->setPosition(vec3(3.0f, 0.0f, 0.0f));

	m_TestGO3 = shared_ptr<GameObject>(loadModelFromFile(modelPath));
	m_TestGO3->loadShaders(vsTextureFilename, fsTextureFilename);
	m_TestGO3->loadDiffuseTexture(diffuseTexturePathBricks);
	m_TestGO3->loadSpecularTexture(specularTexturePathBricks);

	m_TestGO3->setScale(vec3(0.5f, 0.5f, 0.5f));
	m_TestGO3->setPosition(vec3(-3.0f, 0.0f, 0.0f));

	m_Light = shared_ptr<Light>(new Light());
	m_Light->DiffuseColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SpecularColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->Direction = vec3(0.0f, 0.0f, -1.0f);
	m_AmbientLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

void MyGame::onKeyDown(SDL_Keycode keyCode)
{

	if (keyCode == SDLK_LEFT)
	{
		m_TestGO->rotate(vec3(0.0f, -0.1f, 0.0f));
		m_TestGO2->rotate(vec3(0.0f, -0.1f, 0.0f));
		m_TestGO3->rotate(vec3(0.0f, -0.1f, 0.0f));
	}
	else if (keyCode == SDLK_RIGHT)
	{
		m_TestGO->rotate(vec3(0.0f, 0.1f, 0.0f));
		m_TestGO2->rotate(vec3(0.0f, 0.1f, 0.0f));
		m_TestGO3->rotate(vec3(0.0f, 0.1f, 0.0f));
	}
	if (keyCode==SDLK_UP)
	{
		m_TestGO->rotate(vec3(-0.1f,0.0f,0.0f));
		m_TestGO2->rotate(vec3(-0.1f, 0.0f, 0.0f));
		m_TestGO3->rotate(vec3(-0.1f, 0.0f, 0.0f));
	}
	else if (keyCode==SDLK_DOWN)
	{
		m_TestGO->rotate(vec3(0.1f,0.0f,0.0f));
		m_TestGO2->rotate(vec3(0.1f, 0.0f, 0.0f));
		m_TestGO3->rotate(vec3(0.1f, 0.0f, 0.0f));
	}

	if (keyCode == SDLK_a)
	{
		m_CameraPosition -= normalize(cross(m_CameraFront, m_CameraUp) * cameraSpeed);
	}
	if (keyCode == SDLK_d)
	{
		m_CameraPosition += normalize(cross(m_CameraFront, m_CameraUp) * cameraSpeed);
	}
	if (keyCode == SDLK_w)
	{
		m_CameraPosition += normalize(m_CameraFront * cameraSpeed);
	}
	if (keyCode == SDLK_s)
	{
		m_CameraPosition -= normalize(m_CameraFront * cameraSpeed);
	}
}

void MyGame::CamerMovement()
{
	/*if (keyCode == SDLK_a)
	{
		m_CameraPosition -= normalize(cross(m_CameraFront, m_CameraUp) * cameraSpeed);
	}
	if (keyCode == SDLK_d)
	{
		m_CameraPosition += normalize(cross(m_CameraFront, m_CameraUp) * cameraSpeed);
	}
	if (keyCode == SDLK_w)
	{
		m_CameraPosition += cameraSpeed * m_CameraFront;
	}
	if (keyCode == SDLK_s)
	{
		m_CameraPosition -= cameraSpeed * m_CameraFront;
	}*/

}

void MyGame::destroyScene()
{
	m_TestGO->onDestroy();
	m_TestGO2->onDestroy();
	m_TestGO3->onDestroy();
	

}

void MyGame::update()
{
	GameApplication::update();
	
	//SDL_SetRelativeMouseMode(SDL_TRUE);

	GLfloat currentFrame = SDL_GetTicks();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	cameraSpeed = 5.0f * deltaTime;

	//Start move mouse code
	int xpos, ypos;
	SDL_GetMouseState(&xpos, &ypos);

	GLfloat xOffset = xpos - lastX;
	GLfloat yOffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	GLfloat sens = 0.05f;
	xOffset *= sens;
	yOffset *= sens;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	vec3 front;
	front.x = cos(radians(yaw)) * cos(radians(pitch));
	front.y = sin(radians(pitch));
	front.z = sin(radians(yaw)) * cos(radians(pitch));
	m_CameraFront = normalize(front);

	// End move mouse code

	SDL_PumpEvents();

	m_ProjMatrix = perspective(fov, (float)m_WindowWidth / (float)m_WindowHeight, 0.1f, 1000.0f);
	//m_ViewMatrix = lookAt(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	m_ViewMatrix = lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront, m_CameraUp);
	m_TestGO->onUpdate();
	m_TestGO2->onUpdate();
	m_TestGO3->onUpdate();
}

void MyGame::render()
{
	GameApplication::render();
	GLuint currentShader = m_TestGO->getShaderProgram();
	glUseProgram(currentShader);

	GLint ambientLightColourLocation = glGetUniformLocation(currentShader, "directionLight.ambientColour");
	glUniform4fv(ambientLightColourLocation, 1, value_ptr(m_AmbientLightColour));

	GLint diffuseLightColourLocation = glGetUniformLocation(currentShader, "directionLight.diffuseColour");
	glUniform4fv(diffuseLightColourLocation, 1, value_ptr(m_Light->DiffuseColour));

	GLint specularLightColourLocation = glGetUniformLocation(currentShader, "directionLight.specularColour");
	glUniform4fv(specularLightColourLocation, 1, value_ptr(m_Light->SpecularColour));

	GLint lightDirectionLocation = glGetUniformLocation(currentShader, "directionLight.lightDirection");
	glUniform3fv(lightDirectionLocation, 1, value_ptr(m_Light->Direction));

	GLint cameraPositionLocation = glGetUniformLocation(currentShader, "cameraPos");
	glUniform3fv(cameraPositionLocation, 1, value_ptr(m_CameraPosition));

	m_TestGO->onRender(m_ViewMatrix, m_ProjMatrix);

	GLuint currentShader2 = m_TestGO2->getShaderProgram();
	glUseProgram(currentShader2);

	GLint ambientLightColourLocation2 = glGetUniformLocation(currentShader2, "directionLight.ambientColour");
	glUniform4fv(ambientLightColourLocation2, 1, value_ptr(m_AmbientLightColour));

	GLint diffuseLightColourLocation2 = glGetUniformLocation(currentShader2, "directionLight.diffuseColour");
	glUniform4fv(diffuseLightColourLocation2, 1, value_ptr(m_Light->DiffuseColour));

	GLint specularLightColourLocation2 = glGetUniformLocation(currentShader2, "directionLight.specularColour");
	glUniform4fv(specularLightColourLocation2, 1, value_ptr(m_Light->SpecularColour));

	GLint lightDirectionLocation2 = glGetUniformLocation(currentShader2, "directionLight.lightDirection");
	glUniform3fv(lightDirectionLocation2, 1, value_ptr(m_Light->Direction));

	GLint cameraPositionLocation2 = glGetUniformLocation(currentShader2, "cameraPos");
	glUniform3fv(cameraPositionLocation2, 1, value_ptr(m_CameraPosition));

	m_TestGO2->onRender(m_ViewMatrix, m_ProjMatrix);

	GLuint currentShader3 = m_TestGO3->getShaderProgram();
	glUseProgram(currentShader3);

	GLint ambientLightColourLocation3 = glGetUniformLocation(currentShader3, "directionLight.ambientColour");
	glUniform4fv(ambientLightColourLocation3, 1, value_ptr(m_AmbientLightColour));

	GLint diffuseLightColourLocation3 = glGetUniformLocation(currentShader3, "directionLight.diffuseColour");
	glUniform4fv(diffuseLightColourLocation3, 1, value_ptr(m_Light->DiffuseColour));

	GLint specularLightColourLocation3 = glGetUniformLocation(currentShader3, "directionLight.specularColour");
	glUniform4fv(specularLightColourLocation3, 1, value_ptr(m_Light->SpecularColour));

	GLint lightDirectionLocation3 = glGetUniformLocation(currentShader3, "directionLight.lightDirection");
	glUniform3fv(lightDirectionLocation3, 1, value_ptr(m_Light->Direction));

	GLint cameraPositionLocation3 = glGetUniformLocation(currentShader3, "cameraPos");
	glUniform3fv(cameraPositionLocation3, 1, value_ptr(m_CameraPosition));

	m_TestGO3->onRender(m_ViewMatrix, m_ProjMatrix);
}
