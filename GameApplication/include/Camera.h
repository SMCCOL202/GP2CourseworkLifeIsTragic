#ifndef CAMERA_H
#define CAMERA_H

#include "Common.h"
#include "GameApplication.h"

class Camera
{
public:
	Camera();
	~Camera();
	void Update();
protected:
private:
	mat4 m_ProjMatrix;
	mat4 m_ViewMatrix;

};



#endif
