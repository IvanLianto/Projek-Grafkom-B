#pragma once
#ifndef LIGHT_H
#define LIGHT_H

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Object3D.h"
#include "Shader.h"
#include "Transform.h"

class Light {
public:
	Light();
	~Light();

	Object3D object;
	Shader shader;
	Transform transform;
	
	void SetLightPos(glm::vec3 lightPos);
	void SetViewPos(glm::vec3 viewPos);
	void SetLightUp(glm::vec3 lightUp);
	void SetLightDir(glm::vec3 lightDir);
	void SetNearPlane(float nearPlane);
	void SetFarPlane(float farPlane);

	void CreateLight();
	void CreateShadow(GLuint depthMapFBO);
	void UseShader();
	void SetShader(GLuint shaderProgram);
	void Render();

	glm::vec3 GetLightPos();
	glm::vec3 GetViewPos();
	glm::mat4 GetLightView();
	glm::mat4 GetLightProjection();
	glm::mat4 GetLightSpaceMatrix();
	float GetNearPlane();
	float GetFarPlane();
	GLuint GetShader();

private:
	glm::vec3 lightPos;
	glm::vec3 viewPos;
	glm::mat4 lightProjection;
	glm::mat4 lightView;
	glm::mat4 lightSpaceMatrix;
	glm::vec3 lightUp;
	glm::vec3 lightDir;
	float near_plane, far_plane;
};

#endif