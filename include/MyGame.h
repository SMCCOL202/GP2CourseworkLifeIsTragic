#ifndef _MyGame_H
#define _MyGame_H

#include "GameApplication.h"

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
private:
	//matrices
	mat4 m_ViewMatrix;
	mat4 m_ProjMatrix;

	GameObject *m_pGameObject;
	shared_ptr<GameObject> m_TestGO;
	shared_ptr<GameObject> m_TestGO2;
	shared_ptr<GameObject> m_TestGO3;
	shared_ptr<Light> m_Light;
	vec4 m_AmbientLightColour;

	vec3 m_CameraPosition;
};
#endif
