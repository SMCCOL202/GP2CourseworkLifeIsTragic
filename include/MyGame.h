#ifndef _MyGame_H
#define _MyGame_H

#include "GameApplication.h"
#include "Camera.h"

class MyGame:public GameApplication
{
public:
	MyGame();
	~MyGame();

	void render();
	void update();
	void initScene();
	void destroyScene();

	void onKeyDown(SDL_Keycode keyCode);
	void CamerMovement();
	void MoveMouse();

private:
	//matrices
	mat4 m_ViewMatrix;
	mat4 m_ProjMatrix;

	GameObject *m_pGameObject;
	//shared_ptr<GameObject> m_TestGO;
	//shared_ptr<GameObject> m_TestGO2;
	//shared_ptr<GameObject> m_TestGO3;
	vector<shared_ptr<GameObject>> m_GameObjectList;
	shared_ptr<Light> m_Light;
	vec4 m_AmbientLightColour;

	vec3 m_CameraPosition;
	vec3 m_CameraTarget;
	vec3 m_CameraDirection;
	vec3 m_CameraFront;
	vec3 m_CameraUp;
	GLfloat cameraSpeed;

	GLfloat yaw;
	GLfloat pitch;
	GLfloat lastX;
	GLfloat lastY;
	GLfloat fov;
	GLfloat deltaTime;
	GLfloat lastFrame;

};
#endif
