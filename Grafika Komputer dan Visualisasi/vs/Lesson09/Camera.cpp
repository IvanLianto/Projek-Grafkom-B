#include "Camera.h"

Camera::Camera() {
	this->originalPosition = glm::vec3(-2.0f, -1.3f, -2.0f);
	fovy = 45.0f;
	camHeight = 5.0f;
	transform = Transform();

}

Camera::~Camera() {

}

void Camera::SetDefault(bool flag) {
	defaultCamera = flag;
}

void Camera::RenderCamera(GLfloat width, GLfloat height) {
	// Pass perspective projection matrix
	if (defaultCamera) {
		projection = glm::perspective(fovy, width / height, 0.1f, 1000.0f);
	}
	else {
		GLfloat aspect = width / height;
		projection = glm::ortho(-aspect * camHeight / 2.0f, aspect * camHeight / 2.0f, -camHeight / 2.0f, camHeight / 2.0f, 1000.0f, -1000.0f);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// LookAt camera (position, target/direction, up)
	view = glm::lookAt(this->transform.position, this->camDir, this->camUp);

}

void Camera::MoveForward(float camSpeed) {
	float x = this->camDir.x - this->transform.position.x;
	float z = this->camDir.z - this->transform.position.z;
	// forward positive cameraspeed and backward negative -cameraspeed.
	this->transform.position.x = this->transform.position.x + x * camSpeed;
	this->transform.position.z = this->transform.position.z + z * camSpeed;
	this->camDir.x = this->camDir.x + x * camSpeed;
	this->camDir.z = this->camDir.z + z * camSpeed;
}

void Camera::MoveBeside(float camSpeed) {
	float x = this->camDir.x - this->transform.position.x;
	float z = this->camDir.z - this->transform.position.z;
	float orthoX = -z;
	float orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	this->transform.position.x = this->transform.position.x + orthoX * camSpeed;
	this->transform.position.z = this->transform.position.z + orthoZ * camSpeed;
	this->camDir.x = this->camDir.x + orthoX * camSpeed;
	this->camDir.z = this->camDir.z + orthoZ * camSpeed;
}

void Camera::RotateCamera(float speed)
{
	float x = this->camDir.x - this->transform.position.x;
	float z = this->camDir.z - this->transform.position.z;
	this->camDir.z = (float)(this->transform.position.z + glm::sin(speed) * x + glm::cos(speed) * z);
	this->camDir.x = (float)(this->transform.position.x + glm::cos(speed) * x - glm::sin(speed) * z);
}

void Camera::Orbit(GLfloat radius) {
	/*this->angle += angularSpeed;
	if (this->angle > 360.0f)this->angle -= 360.0f;
	GLfloat newX = this->originalPosition.x * glm::sin(glm::radians(angle));
	GLfloat newZ = this->originalPosition.z * glm::cos(glm::radians(angle));*/
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	transform.SetPosition(glm::vec3(camX, this->transform.position.y, camZ));
}

void Camera::Zoom(GLfloat value) {
	this->fovy += value;
}

void Camera::SetCameraFront(glm::vec3 front) {
	cameraFront = front;
}

void Camera::SetCameraPos(glm::vec3 pos) {
	cameraPos = pos;
}

void Camera::SetCameraDirection(glm::vec3 camDir) {
	this->camDir = camDir;
}

void Camera::SetCameraUp(glm::vec3 camUp) {
	this->camUp = camUp;
}