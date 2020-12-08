#include "Camera.h"

Camera::Camera() {
	this->originalPosition = glm::vec3(-2.0f, -1.3f, -2.0f);
	this->angle = 90;
	camHeight = 5.0f;
	transform = Transform();
	Orbit(this->angle);
}

Camera::~Camera() {

}

void Camera::SetDefault(bool flag) {
	defaultCamera = flag;
}

void Camera::RenderCamera(GLfloat width, GLfloat height) {
	// Pass perspective projection matrix
	if (defaultCamera) {
		projection = glm::perspective(45.0f, width / height, 0.1f, 100.0f);
	}
	else {
		GLfloat aspect = width / height;
		projection = glm::ortho(-aspect * camHeight / 2.0f, aspect * camHeight / 2.0f, -camHeight / 2.0f, camHeight / 2.0f, 1000.0f, -1000.0f);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// LookAt camera (position, target/direction, up)
	view = glm::lookAt(this->transform.position, glm::vec3(0.0, -2.0, 0.0), glm::vec3(0.0, 5.0, 0.0));

}

void Camera::Orbit(GLfloat angularSpeed) {
	this->angle += angularSpeed;
	if (this->angle > 360.0f)this->angle -= 360.0f;
	GLfloat newX = this->originalPosition.x * glm::sin(glm::radians(angle));
	GLfloat newZ = this->originalPosition.z * glm::cos(glm::radians(angle));
	transform.SetPosition(glm::vec3(newX, this->originalPosition.y, newZ));
}

void Camera::Zoom(GLfloat value) {
	this->camHeight += value;
}

void Camera::SetCameraFront(glm::vec3 front) {
	cameraFront = front;
}

void Camera::SetCameraPos(glm::vec3 pos) {
	cameraPos = pos;
}