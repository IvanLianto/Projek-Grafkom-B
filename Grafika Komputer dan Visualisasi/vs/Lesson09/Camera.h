#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "Transform.h"

class Camera {
public:
	Camera();
	~Camera();

	glm::mat4 projection;
	glm::mat4 view;
	glm::vec3 originalPosition;
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 camUp;
	glm::vec3 camDir;
	float fovy;
	GLfloat angle;
	GLfloat camHeight;
	Transform transform;

	void SetDefault(bool flag);
	void RenderCamera(GLfloat width, GLfloat height);

	void SetCameraPos(glm::vec3 pos);
	void SetCameraFront(glm::vec3 front);

	void Orbit(GLfloat angularSpeed);

	void Zoom(GLfloat value);

	void SetCameraUp(glm::vec3 camUp);
	void SetCameraDirection(glm::vec3 camDir);

	void MoveForward(float camSpeed);
	void MoveBeside(float camSpeed);
	void RotateCamera(float camSpeed);

private:
	bool defaultCamera = true;
};

#endif