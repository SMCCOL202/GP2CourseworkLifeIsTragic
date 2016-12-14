#include "MyGame.h"

const std::string ASSET_PATH = "assets";
const std::string SHADER_PATH = "/shaders";
const std::string TEXTURE_PATH = "/textures";
const std::string MODEL_PATH = "/models";

MyGame::MyGame()
{
	m_CameraPosition = vec3(0.0f, 0.0f, 30.0f);
	m_CameraFront = vec3(0.0f, 0.0f, -1.0f);
	m_CameraUp = vec3(0.0f, 10.0f, 0.0f);
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
	//SDL_WarpMouseInWindow(m_pWindow, m_WindowWidth / 2, m_WindowHeight / 2);
	
	string modelPath = ASSET_PATH + MODEL_PATH + "/Earth.fbx";
	string modelWoodboard = ASSET_PATH + MODEL_PATH + "/woodboard.fbx";
	string modelAmmoBox = ASSET_PATH + MODEL_PATH + "/Ammo_box.fbx";
	string modelBarrel = ASSET_PATH + MODEL_PATH + "/barrel.fbx";

	string vsTextureFilename = ASSET_PATH + SHADER_PATH + "/lightTextureVS.glsl";
	string fsTextureFilename = ASSET_PATH + SHADER_PATH + "/lightTextureFS.glsl";
	string vsNormalFilename = ASSET_PATH + SHADER_PATH + "/normalMappingVS.glsl";
	string fsNormalFilename = ASSET_PATH + SHADER_PATH + "/normalMappingFS.glsl";
	string vsParallaxFilename = ASSET_PATH + SHADER_PATH + "/parallaxMappingVS.glsl";
	string fsParallaxFilename = ASSET_PATH + SHADER_PATH + "/parallaxMappingFS.glsl";

	/*string diffuseTexturePathEarth = ASSET_PATH + TEXTURE_PATH + "/earth_diff.png";
	string specularTexturePathEarth = ASSET_PATH + TEXTURE_PATH + "/earth_spec.png";
	string normalTexturePathEarth = ASSET_PATH + TEXTURE_PATH + "/earth_norm.png";
	string parallaxTexturePathEarth = ASSET_PATH + TEXTURE_PATH + "/earth_height.png";*/

	string diffuseTexturePathBricks = ASSET_PATH + TEXTURE_PATH + "/bricks_diff.jpg";
	string specularTexturePathBricks = ASSET_PATH + TEXTURE_PATH + "/bricks_spec.png";
	string normalTexturePathBricks = ASSET_PATH + TEXTURE_PATH + "/bricks_norm.png";
	string parallaxTexturePathBricks = ASSET_PATH + TEXTURE_PATH + "/bricks_height.png";

	string diffuseTexturePathBoard = ASSET_PATH + TEXTURE_PATH + "/boards_color.png";
	string specularTexturePathBoard = ASSET_PATH + TEXTURE_PATH + "/boards_spec.png";
	string normalTexturePathBoard = ASSET_PATH + TEXTURE_PATH + "/boards_normal.png";
	string parallaxTexturePathBoard = ASSET_PATH + TEXTURE_PATH + "/boards_height.png";

	string diffuseTexturePathAmmoBox = ASSET_PATH + TEXTURE_PATH + "/ammo_box_color_01.png";
	string specularTexturePathAmmoBox = ASSET_PATH + TEXTURE_PATH + "/ammo_box_spec_03.png";
	string normalTexturePathAmmoBox = ASSET_PATH + TEXTURE_PATH + "/ammo_box_nmap_03.png";

	string diffuseTexturePathBarrel = ASSET_PATH + TEXTURE_PATH + "/barrel_color_01.png";
	string specularTexturePathBarrel = ASSET_PATH + TEXTURE_PATH + "/barrel_spec_03.png";
	string normalTexturePathBarrel = ASSET_PATH + TEXTURE_PATH + "/barrel_nmap_03.png";

	//Ammo Box Model
	shared_ptr<GameObject>m_TestGO = shared_ptr<GameObject>(loadModelFromFile(modelAmmoBox));
	m_TestGO->loadShaders(vsNormalFilename, fsNormalFilename);
	m_TestGO->loadDiffuseTexture(diffuseTexturePathAmmoBox);
	m_TestGO->loadSpecularTexture(specularTexturePathAmmoBox);
	m_TestGO->loadNormalTexture(normalTexturePathAmmoBox);

	m_TestGO->setScale(vec3(0.3f, 0.3f, 0.3f));
	m_TestGO->setPosition(vec3(-15.0f, 0.0f, 0.0f)); 
	m_TestGO->setRotation(vec3(0.0f, 200.0f, 0.0f));
	m_GameObjectList.push_back(m_TestGO);

	//Woodboard Model
	m_TestGO = shared_ptr<GameObject>(loadModelFromFile(modelWoodboard));
	m_TestGO->loadShaders(vsParallaxFilename, fsParallaxFilename);
	m_TestGO->loadDiffuseTexture(diffuseTexturePathBoard);
	m_TestGO->loadSpecularTexture(specularTexturePathBoard);
	m_TestGO->loadNormalTexture(normalTexturePathBoard);
	m_TestGO->loadHeightTexture(parallaxTexturePathBoard);

	m_TestGO->setScale(vec3(0.2f, 0.2f, 0.2f));
	m_TestGO->setPosition(vec3(10.0f, 0.0f, 0.0f));
	m_TestGO->setRotation(vec3(300.0f, 0.0f, 0.0f));
	m_GameObjectList.push_back(m_TestGO);

	//Barrel Model
	m_TestGO = shared_ptr<GameObject>(loadModelFromFile(modelBarrel));
	m_TestGO->loadShaders(vsNormalFilename, fsNormalFilename);
	m_TestGO->loadDiffuseTexture(diffuseTexturePathBarrel);
	m_TestGO->loadSpecularTexture(specularTexturePathBarrel);
	m_TestGO->loadNormalTexture(normalTexturePathBarrel);

	m_TestGO->setScale(vec3(0.1f, 0.1f, 0.1f));
	m_TestGO->setPosition(vec3(0.0f, 0.0f, 0.0f));
	
	m_GameObjectList.push_back(m_TestGO);

	m_Light = shared_ptr<Light>(new Light());
	m_Light->DiffuseColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SpecularColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->Direction = vec3(0.0f, 0.0f, -1.0f);
	m_AmbientLightColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

void MyGame::onKeyDown(SDL_Keycode keyCode)
{
	for (auto& go : m_GameObjectList)
	{
		if (keyCode == SDLK_LEFT)
		{
			go->rotate(vec3(0.0f, -0.1f, 0.0f));

		}
		else if (keyCode == SDLK_RIGHT)
		{
			go->rotate(vec3(0.0f, 0.1f, 0.0f));

		}
		if (keyCode == SDLK_UP)
		{
			go->rotate(vec3(-0.1f, 0.0f, 0.0f));

		}
		else if (keyCode == SDLK_DOWN)
		{
			go->rotate(vec3(0.1f, 0.0f, 0.0f));
		}
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

}

void MyGame::MoveMouse()
{
	//SDL_SetRelativeMouseMode(SDL_TRUE);
	GLfloat currentFrame = SDL_GetTicks();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	cameraSpeed = 5.0f * deltaTime;

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
}

void MyGame::destroyScene()
{
	for (auto& go : m_GameObjectList)
	{
		go->onDestroy();
	}

	m_GameObjectList.clear();

}

void MyGame::update()
{
	GameApplication::update();
	
	MoveMouse();

	SDL_PumpEvents();

	m_ProjMatrix = perspective(fov, (float)m_WindowWidth / (float)m_WindowHeight, 0.1f, 1000.0f);
	//m_ViewMatrix = lookAt(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	m_ViewMatrix = lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront, m_CameraUp);
	
	for (auto& go : m_GameObjectList)
	{
		go->onUpdate();
	}
}

void MyGame::render()
{
	GameApplication::render();
	for (auto& go : m_GameObjectList)
	{
		GLuint currentShader = go->getShaderProgram();

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

		go->onRender(m_ViewMatrix, m_ProjMatrix);
	}

}
