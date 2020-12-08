#include "Shader.h"

Shader::Shader() {

}

Shader::~Shader() {

}

void Shader::BuildShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath) {
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode, fragmentCode, geometryCode;
	std::ifstream vShaderFile, fShaderFile, gShaderFile;
	// ensures ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// Open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// If geometry shader path is present, also load a geometry shader
		if (geometryPath != nullptr)
		{
			gShaderFile.open(geometryPath);
			std::stringstream gShaderStream;
			gShaderStream << gShaderFile.rdbuf();
			gShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::ifstream::failure e)
	{
		Err("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
	}
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();
	// 2. Compile shaders
	GLuint vertex, fragment;
	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	CheckShaderErrors(vertex, "VERTEX");
	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	CheckShaderErrors(fragment, "FRAGMENT");
	// If geometry shader is given, compile geometry shader
	GLuint geometry;
	if (geometryPath != nullptr)
	{
		const GLchar* gShaderCode = geometryCode.c_str();
		geometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry, 1, &gShaderCode, NULL);
		glCompileShader(geometry);
		CheckShaderErrors(geometry, "GEOMETRY");
	}
	// Shader Program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertex);
	glAttachShader(shaderProgram, fragment);
	if (geometryPath != nullptr)
		glAttachShader(shaderProgram, geometry);
	glLinkProgram(shaderProgram);
	CheckShaderErrors(shaderProgram, "PROGRAM");
	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	if (geometryPath != nullptr)
		glDeleteShader(geometry);
}

GLuint Shader::GetShader() {
	return shaderProgram;
}

GLuint Shader::GetBuildShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath) {
	BuildShader(vertexPath, fragmentPath);
	return shaderProgram;
}

void Shader::SetShader(GLuint shaderProgram) {
	this->shaderProgram = shaderProgram;
}

void Shader::Use() {
	glUseProgram(shaderProgram);
}

void Shader::UseShader(GLuint program) {
	glUseProgram(program);
}

void Shader::UnUse() {
	glUseProgram(0);
}

void Shader::Err(std::string errorString) {
	std::cout << errorString << std::endl;
	glfwTerminate();
	exit(1);
}

void Shader::CheckShaderErrors(GLuint shader, std::string type) {
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			Err("| ERROR::::SHADER-COMPILATION-ERROR of type: " + type + "|\n" + infoLog + "\n| -- --------------------------------------------------- -- |");
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			Err("| ERROR::::PROGRAM-LINKING-ERROR of type: " + type + "|\n" + infoLog + "\n| -- --------------------------------------------------- -- |");
		}
	}
}