#pragma once

#ifndef OBJECT_3D_H
#define OBJECT_3D_H
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SOIL/SOIL.h>
#include "Shader.h"
#include "Transform.h"

class Object3D {
public:
	Object3D();
	~Object3D();

	Transform transform;

	void CreateObject(const char* vertexPath, const char* fragmentPath);
	void BuildObject(float* _vertices, size_t verticesSize, unsigned int* _indices, size_t indicesSize);
	GLuint GetVAO();
	GLuint GetVBO();
	GLuint GetEBO();
	GLuint GetShader();
	void SetShader(GLuint shader);
	void VerticesDraw(int verticesDraw);
	void Render(GLuint depthMap);
	void RenderLight(GLuint shader);
	void ApplyTexture(const char* _texturePath);
	void DeInit();
	void UseShader();

private:
	GLuint VAO, VBO, EBO;
	GLuint textureID;
	Shader shader;
	GLuint verticesDraw;
	bool textureEnabled;
};

#endif