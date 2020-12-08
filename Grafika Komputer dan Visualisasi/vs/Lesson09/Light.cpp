#include "Light.h"

Light::Light() {
	shader = Shader();
}

Light::~Light() {

}

void Light::CreateLight() {

}

void Light::Render() {

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

void Light::SetShader(GLuint shaderProgram) {
	this->shader.SetShader(shaderProgram);
}

GLuint Light::GetShader() {
	return shader.GetShader();
}

void Light::UseShader() {
	shader.Use();
}