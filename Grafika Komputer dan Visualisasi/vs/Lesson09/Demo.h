#pragma once
#include "RenderEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <SOIL/SOIL.h>
#include "Shader.h"
#include "Object3D.h"
#include "Light.h"
#include "Camera.h"

class Demo :
	public RenderEngine
{
public:
	Demo();
	~Demo();

	Object3D cube;
	Object3D cube2;
	Object3D cube3;
	Object3D cube4;
	Object3D cube5;
	Object3D cube6;
	Object3D plane;
private:
	GLuint depthmapShader, shadowmapShader, texture_id, plane_texture, stexture, stexture2, depthMapFBO, depthMap;
	GLuint VAO, VBO, EBO, planeVBO, planeVAO, planeEBO;
	Shader shader;
	Light light;
	Camera camera;
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	virtual void Init();
	virtual void DeInit();
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow *window);
	void BuildObject(float* _vertices, size_t verticesSize, unsigned int* _indices, size_t indicesSize);
	void BuildTexturedPlane();
	void DrawTexturedCube(GLuint shader);
	void DrawTexturedPlane(GLuint shader);
	void BuildDepthMap();
	void BuildShaders();
	void ApplyTexture(const char* _texturePath);
	void BuildObject();
	// Build Plane
	void BuildPlane();
	//Build Cube
	void BuildCube();
	void BuildCube2();
	void BuildCube3();
	void BuildCube4();
	void BuildCube5();
	void BuildCube6();
	// Build Light
	void BuildLight();
};

