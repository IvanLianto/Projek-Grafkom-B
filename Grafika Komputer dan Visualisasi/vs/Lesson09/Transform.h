#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Shader.h"

class Transform {
public:
	Transform();
	~Transform();

	glm::mat4 model;

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	//glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 origin = glm::vec3(0.0f, 0.0f, 0.0f);

	void Translate(glm::vec3 direction);
	void Rotate(glm::vec3 direction, float angle);
	void Scale(glm::vec3 scale);
	void SetOrigin(glm::vec3 origin);
	void SetPosition(glm::vec3 newPosition);
	void setOrientation(glm::vec3 direction, float angle);
	void Execute(Shader shader);

private:
	glm::vec3 rotationDirectionTemp = glm::vec3(1.0f, 1.0f, 1.0f);
	float angleTemp = 0.0f;
};

#endif
