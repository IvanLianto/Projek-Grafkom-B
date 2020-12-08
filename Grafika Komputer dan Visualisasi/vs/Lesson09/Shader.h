#ifndef SHADER_H
#define SHADER_H

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	Shader();
	~Shader();
	void BuildShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	GLuint GetBuildShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	GLuint GetShader();
	void Use();
	void UseShader(GLuint program);
	void UnUse();
	void SetShader(GLuint shaderProgram);
private:
	GLuint shaderProgram;
	void Err(std::string errorString);
	void CheckShaderErrors(GLuint shader, std::string type);
};


#endif 