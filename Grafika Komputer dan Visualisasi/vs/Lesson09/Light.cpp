#include "Light.h"

Light::Light() {
	shader = Shader();
	transform = Transform();
}

Light::~Light() {

}

void Light::CreateLight() {

}

void Light::Render() {

}

void Light::CreateShadow(GLuint depthMapFBO) {
	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, this->near_plane, this->far_plane);
	lightView = glm::lookAt(this->transform.position, this->lightDir, this->lightUp);
	lightSpaceMatrix = lightProjection * lightView;

	glUniformMatrix4fv(glGetUniformLocation(GetShader(), "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(GetLightSpaceMatrix()));
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Light::SetLightPos(glm::vec3 lightPos) {
	this->lightPos = lightPos;
	shader.Use();
	glUniform3f(glGetUniformLocation(shader.GetShader(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
}

glm::vec3 Light::GetLightPos() {
	return lightPos;
}

void Light::SetViewPos(glm::vec3 viewPos) {
	this->viewPos = viewPos;
	shader.Use();
	glUniform3f(glGetUniformLocation(shader.GetShader(), "viewPos"), viewPos.x, viewPos.y, viewPos.z);
}

glm::vec3 Light::GetViewPos() {
	return viewPos;
}

void Light::SetLightUp(glm::vec3 lightUp) {
	this->lightUp = lightUp;
}

void Light::SetLightDir(glm::vec3 lightDir) {
	this->lightDir = lightDir;
}

void Light::SetShader(GLuint shaderProgram) {
	this->shader.SetShader(shaderProgram);
}

void Light::SetNearPlane(float nearPlane) {
	this->near_plane = nearPlane;
}

void Light::SetFarPlane(float farPlane) {
	this->far_plane = farPlane;
}

glm::mat4 Light::GetLightSpaceMatrix() {
	return lightSpaceMatrix;
}

GLuint Light::GetShader() {
	return shader.GetShader();
}

void Light::UseShader() {
	shader.Use();
}