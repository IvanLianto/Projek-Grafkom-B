#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Object3D.h"
#include "Shader.h"

class Light {
public:
	Light();
	~Light();
	void CreateLight();
	void SetLightPos(glm::vec3 lightPos);
	glm::vec3 GetLightPos();
	void SetViewPos(glm::vec3 viewPos);
	glm::vec3 GetViewPos();
	GLuint GetShader();
	void UseShader();
	void SetShader(GLuint shaderProgram);
	void Render();
private:
	glm::vec3 lightPos;
	glm::vec3 viewPos;
	Object3D object;
	Shader shader;
};

#endif