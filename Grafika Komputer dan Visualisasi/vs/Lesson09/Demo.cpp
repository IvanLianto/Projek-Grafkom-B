#include "Demo.h"

Demo::Demo() {
	shader = Shader();
	light = Light();
	camera = Camera();
}


Demo::~Demo() {
}



void Demo::Init() {
	cube = Object3D();
	cube2 = Object3D();
	cubeup = Object3D();
	cube2up = Object3D();
	cube3 = Object3D();
	cube3up = Object3D();
	cube4 = Object3D();
	cube4up = Object3D();
	cube5 = Object3D();
	cube6 = Object3D();
	plane = Object3D();
	BuildShaders();
	BuildDepthMap();
	BuildCamera();
	BuildCube();
	BuildCube2();
	BuildCubeup();
	BuildCube2up();
	BuildCube3();
	BuildCube3up();
	BuildCube4();
	BuildCube4up();
	BuildCube5();
	BuildCube6();
	BuildPlane();
	BuildLight();
	camera.SetDefault(true);
}

void Demo::DeInit() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	plane.DeInit();
	cube.DeInit();
	cube2.DeInit();
	cubeup.DeInit();
	cube2up.DeInit();
	cube3.DeInit();
	cube3up.DeInit();
	cube4.DeInit();
	cube4up.DeInit();
	cube5.DeInit();
	cube6.DeInit();
	glDeleteBuffers(1, &depthMapFBO);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Demo::ProcessInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void Demo::Update(double deltaTime) {

	// zoom camera
	// -----------
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) { // Zoom in
		if (camera.fovy < 90) {
			camera.Zoom(0.0001f);
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) { // Zoom out
		if (camera.fovy > 0) {
			camera.Zoom(-0.0001f);
		}
	}


	// Move Camera
	// Move Forward n Backward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { // Forward
		camera.MoveForward(0.001f);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { // Backward
		camera.MoveForward(-0.001f);
	}

	// Move Right n Left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { // Left
		camera.MoveBeside(-0.001f);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { // Right
		camera.MoveBeside(0.001f);
	}

	CursorMovement();
}

void Demo::Render() {

	glEnable(GL_DEPTH_TEST);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	glViewport(0, 0, this->screenWidth, this->screenHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	BuildObject();

	glDisable(GL_DEPTH_TEST);

	// Step 1 Render depth of scene to texture
	// ----------------------------------------
	/*glm::mat4 lightProjection, lightView;
	glm::mat4 lightSpaceMatrix;
	float near_plane = 1.0f, far_plane = 7.5f;
	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0, 1.0, 0.0));
	lightSpaceMatrix = lightProjection * lightView;*/

	// render scene from light's point of view
	/*shader.UseShader(this->depthmapShader);
	glUniformMatrix4fv(glGetUniformLocation(this->depthmapShader, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
	glViewport(0, 0, this->SHADOW_WIDTH, this->SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);*/
	//DrawTexturedCube(this->depthmapShader);
	//DrawTexturedPlane(this->depthmapShader);
	/*glBindFramebuffer(GL_FRAMEBUFFER, 0);*/



	// Step 2 Render scene normally using generated depth map
	// ------------------------------------------------------

	// Pass perspective projection matrix
	//shader.UseShader(this->shadowmapShader);
	//glm::mat4 projection = glm::perspective(45.0f, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	// LookAt camera (position, target/direction, up)
	/*glm::vec3 cameraPos = glm::vec3(0, 5, 2);
	glm::vec3 cameraFront = glm::vec3(0, 0, 0);*/
	//const float radius = 5.0f;
	//float camX = sin(glfwGetTime()) * radius;
	//float camZ = cos(glfwGetTime()) * radius;
	//glm::mat4 view;
	//view = glm::lookAt(glm::vec3(1.0, 50.0, 1.0), glm::vec3(0.0, -2.0, 0.0), glm::vec3(0.0, 5.0, 0.0));

	// Setting Light Attributes
	//glUniformMatrix4fv(glGetUniformLocation(this->shadowmapShader, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

	// Configure Shaders


}

void Demo::CursorMovement() {
	// update camera rotation
	// ----------------------
	double mouseX, mouseY;
	double midX = screenWidth / 2;
	double midY = screenHeight / 2;
	float angleY = 0.0f;
	float angleZ = 0.0f;

	// Get mouse position
	glfwGetCursorPos(window, &mouseX, &mouseY);
	if ((mouseX == midX) && (mouseY == midY)) {
		return;
	}

	// Set mouse position
	glfwSetCursorPos(window, midX, midY);

	// Get the direction from the mouse cursor, set a resonable maneuvering speed
	angleY = (float)((midX - mouseX)) / 1000;
	angleZ = (float)((midY - mouseY)) / 1000;

	// The higher the value is the faster the camera looks around.
	camera.camDir.y += angleZ * 2;

	// limit the rotation around the x-axis
	if ((camera.camDir.y - camera.transform.position.y) > 8) {
		camera.camDir.y = camera.transform.position.y + 8;
	}
	if ((camera.camDir.y - camera.transform.position.y) < -8) {
		camera.camDir.y = camera.transform.position.y - 8;
	}

	camera.RotateCamera(-angleY);
}

void Demo::BuildObject() {
	// Render Camera
	camera.RenderCamera(this->screenWidth, this->screenHeight);
	//camera.Orbit(100.0);

	// Configurate Shader
	glUniform1i(glGetUniformLocation(this->shadowmapShader, "diffuseTexture"), 0);
	glUniform1i(glGetUniformLocation(this->shadowmapShader, "shadowMap"), 1);

	// Render light
	light.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(light.GetShader(), "projection"), 1, GL_FALSE, glm::value_ptr(camera.projection));
	glUniformMatrix4fv(glGetUniformLocation(light.GetShader(), "view"), 1, GL_FALSE, glm::value_ptr(camera.view));
	glUniformMatrix4fv(glGetUniformLocation(light.GetShader(), "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(light.GetLightSpaceMatrix()));

	// Render floor
	plane.UseShader();
	plane.Render(depthMap);

	// Render cube
	cube.UseShader();
	cube.Render(depthMap);

	cube2.UseShader();
	cube2.Render(depthMap);

	cube3.UseShader();
	cube3.Render(depthMap);

	cube4.UseShader();
	cube4.Render(depthMap);

	cube4up.UseShader();
	cube4up.Render(depthMap);

	cube5.UseShader();
	cube5.Render(depthMap);

	cube3up.UseShader();
	cube3up.Render(depthMap);

	cube2up.UseShader();
	cube2up.Render(depthMap);

	cubeup.UseShader();
	cubeup.Render(depthMap);


	cube6.UseShader();
	cube6.Render(depthMap);

}

void Demo::BuildCamera() {
	camera.SetCameraPos(glm::vec3(0, 5, 2));
	camera.SetCameraFront(glm::vec3(0, 0, 0));
	camera.transform.SetPosition(glm::vec3(0.0, 16.0, 0.0)); // diubah-ubah
	camera.SetCameraDirection(glm::vec3(64.0, 16.0, 0.0)); // diubah-ubah
	camera.SetCameraUp(glm::vec3(0.0, 1.0, 0.0)); // diubah-ubah
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Demo::BuildLight() {
	light.SetShader(this->depthmapShader);
	light.transform.SetPosition(glm::vec3(0.0f, 10.0f, 0.0f));
	light.SetLightDir(glm::vec3(0.0f, 0.0f, 0.0f));
	light.SetLightUp(glm::vec3(0.0, 1.0, 0.0));
	light.SetFarPlane(7.5f);
	light.SetNearPlane(1.0f);
	light.CreateShadow(depthMapFBO);

	light.SetShader(this->shadowmapShader);
	light.SetLightPos(glm::vec3(0.0f, 50.0f, 0.0f));
	light.SetViewPos(glm::vec3(0.0f, 50.0f, 0.0f));
}

void Demo::BuildPlane()
{
	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		-100.0f,	-0.5f, -100.0f,  0,  0, 0.0f,  1.0f,  0.0f,
		100.0f,	-0.5f, -100.0f, 100,  0, 0.0f,  1.0f,  0.0f,
		100.0f,	-0.5f,  100.0f, 100, 100, 0.0f,  1.0f,  0.0f,
		-100.0f,	-0.5f,  100.0f,  0, 100, 0.0f,  1.0f,  0.0f,
	};

	GLuint indices[] = { 0,  2,  1,  0,  3,  2 };

	plane.SetShader(shadowmapShader);
	plane.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));

	plane.ApplyTexture("Floor.png");
	plane.VerticesDraw(sizeof(indices));
	cube.transform.SetOrigin(glm::vec3(0.0f, 0.0f, 0.0f));
}

void Demo::BuildCube() //rak jualan 1
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords, normal
		// front
		0.0, 0.0, 0.0, 0, 0, 0.0f,  0.0f,  1.0f, // 0
		64.0, 0.0, 0.0, 1, 0,  0.0f,  0.0f,  1.0f, // 1
		64.0,  16.0, 0.0, 1, 1,  0.0f,  0.0f,  1.0f, // 2
		0.0,  16.0, 0.0, 0, 1, 0.0f,  0.0f,  1.0f, // 3

		 // right
		 64.0,  0.0,  8.0, 0, 0, 1.0f,  0.0f,  0.0f, // 4
		 64.0,  0.0, 0.0, 1, 0, 1.0f,  0.0f,  0.0f, // 5
		 64.0, 16.0, 0.0, 1, 1, 1.0f,  0.0f,  0.0f, // 6
		 64.0, 16.0,  8.0, 0, 1, 1.0f,  0.0f,  0.0f, // 7

		// back
		0.0, 0.0, 8.0, 0, 0, 0.0f,  0.0f,  -1.0f, // 8 
		64.0,  0.0, 8.0, 1, 0, 0.0f,  0.0f,  -1.0f, // 9
		64.0,   16.0, 8.0, 1, 1, 0.0f,  0.0f,  -1.0f, // 10
		0.0,  16.0, 8.0, 0, 1, 0.0f,  0.0f,  -1.0f, // 11

		 // left
		 0.0, 0.0, 8.0, 0, 0, -1.0f,  0.0f,  0.0f, // 12
		 0.0, 0.0,  0.0, 1, 0, -1.0f,  0.0f,  0.0f, // 13
		 0.0,  16.0,  0.0, 1, 1, -1.0f,  0.0f,  0.0f, // 14
		 0.0,  16.0, 8.0, 0, 1, -1.0f,  0.0f,  0.0f, // 15

		// upper
		0.0, 16.0,  0.0, 0, 0,   0.0f,  1.0f,  0.0f, // 16
		64.0, 16.0, 0.0, 1, 0,   0.0f,  1.0f,  0.0f, // 17
		64.0, 16.0, 8.0, 1, 1,  0.0f,  1.0f,  0.0f, // 18
		0.0, 16.0, 8.0, 0, 1,   0.0f,  1.0f,  0.0f, // 19

		// bottom
		0.0, 0.0, 0.0, 0, 0, 0.0f,  -1.0f,  0.0f, // 20
		64.0, 0.0, 0.0, 1, 0,  0.0f,  -1.0f,  0.0f, // 21
		64.0, 0.0,  8.0, 1, 1,  0.0f,  -1.0f,  0.0f, // 22
		0.0, 0.0,  8.0, 0, 1, 0.0f,  -1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,  // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		/*16, 18, 17, 16, 19, 18,*/  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	cube.SetShader(shadowmapShader);
	cube.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));
	cube.ApplyTexture("rak_beta.png");
	cube.VerticesDraw(sizeof(indices));
	cube.transform.SetPosition(glm::vec3(-24.0f, 0.5f, 8.0f));
	cube.transform.Scale(glm::vec3(1.0f, 1.0f, 1.0f));
}

void Demo::BuildCube2() // rak jualan 2
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords, normal
		// front
		0.0, 0.0, 0.0, 0, 0, 0.0f,  0.0f,  1.0f, // 0
		64.0, 0.0, 0.0, 1, 0,  0.0f,  0.0f,  1.0f, // 1
		64.0,  16.0, 0.0, 1, 1,  0.0f,  0.0f,  1.0f, // 2
		0.0,  16.0, 0.0, 0, 1, 0.0f,  0.0f,  1.0f, // 3

		 // right
		 64.0,  0.0,  8.0, 0, 0, 1.0f,  0.0f,  0.0f, // 4
		 64.0,  0.0, 0.0, 1, 0, 1.0f,  0.0f,  0.0f, // 5
		 64.0, 16.0, 0.0, 1, 1, 1.0f,  0.0f,  0.0f, // 6
		 64.0, 16.0,  8.0, 0, 1, 1.0f,  0.0f,  0.0f, // 7

		// back
		0.0, 0.0, 8.0, 0, 0, 0.0f,  0.0f,  -1.0f, // 8 
		64.0,  0.0, 8.0, 1, 0, 0.0f,  0.0f,  -1.0f, // 9
		64.0,   16.0, 8.0, 1, 1, 0.0f,  0.0f,  -1.0f, // 10
		0.0,  16.0, 8.0, 0, 1, 0.0f,  0.0f,  -1.0f, // 11

		 // left
		 0.0, 0.0, 8.0, 0, 0, -1.0f,  0.0f,  0.0f, // 12
		 0.0, 0.0,  0.0, 1, 0, -1.0f,  0.0f,  0.0f, // 13
		 0.0,  16.0,  0.0, 1, 1, -1.0f,  0.0f,  0.0f, // 14
		 0.0,  16.0, 8.0, 0, 1, -1.0f,  0.0f,  0.0f, // 15

		// upper
		0.0, 16.0,  0.0, 0, 0,   0.0f,  1.0f,  0.0f, // 16
		64.0, 16.0, 0.0, 1, 0,   0.0f,  1.0f,  0.0f, // 17
		64.0, 16.0, 8.0, 1, 1,  0.0f,  1.0f,  0.0f, // 18
		0.0, 16.0, 8.0, 0, 1,   0.0f,  1.0f,  0.0f, // 19

		// bottom
		0.0, 0.0, 0.0, 0, 0, 0.0f,  -1.0f,  0.0f, // 20
		64.0, 0.0, 0.0, 1, 0,  0.0f,  -1.0f,  0.0f, // 21
		64.0, 0.0,  8.0, 1, 1,  0.0f,  -1.0f,  0.0f, // 22
		0.0, 0.0,  8.0, 0, 1, 0.0f,  -1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		/*16, 18, 17, 16, 19, 18,*/  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	cube2.SetShader(shadowmapShader);
	cube2.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));
	cube2.ApplyTexture("rak_beta.png");
	cube2.VerticesDraw(sizeof(indices));
	cube2.transform.SetPosition(glm::vec3(-24.0f, 0.5f, -16.0f));
	cube2.transform.Scale(glm::vec3(1.0f, 1.0f, 1.0f));
}

void Demo::BuildCubeup() //rak jualan 1
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords, normal
		// front
		0.0, 0.0, 0.0, 0, 0, 0.0f,  0.0f,  1.0f, // 0
		64.0, 0.0, 0.0, 1, 0,  0.0f,  0.0f,  1.0f, // 1
		64.0,  16.0, 0.0, 1, 1,  0.0f,  0.0f,  1.0f, // 2
		0.0,  16.0, 0.0, 0, 1, 0.0f,  0.0f,  1.0f, // 3

		 // right
		 64.0,  0.0,  8.0, 0, 0, 1.0f,  0.0f,  0.0f, // 4
		 64.0,  0.0, 0.0, 1, 0, 1.0f,  0.0f,  0.0f, // 5
		 64.0, 16.0, 0.0, 1, 1, 1.0f,  0.0f,  0.0f, // 6
		 64.0, 16.0,  8.0, 0, 1, 1.0f,  0.0f,  0.0f, // 7

		// back
		0.0, 0.0, 8.0, 0, 0, 0.0f,  0.0f,  -1.0f, // 8 
		64.0,  0.0, 8.0, 1, 0, 0.0f,  0.0f,  -1.0f, // 9
		64.0,   16.0, 8.0, 1, 1, 0.0f,  0.0f,  -1.0f, // 10
		0.0,  16.0, 8.0, 0, 1, 0.0f,  0.0f,  -1.0f, // 11

		 // left
		 0.0, 0.0, 8.0, 0, 0, -1.0f,  0.0f,  0.0f, // 12
		 0.0, 0.0,  0.0, 1, 0, -1.0f,  0.0f,  0.0f, // 13
		 0.0,  16.0,  0.0, 1, 1, -1.0f,  0.0f,  0.0f, // 14
		 0.0,  16.0, 8.0, 0, 1, -1.0f,  0.0f,  0.0f, // 15

		// upper
		0.0, 16.0,  0.0, 0, 0,   0.0f,  1.0f,  0.0f, // 16
		64.0, 16.0, 0.0, 1, 0,   0.0f,  1.0f,  0.0f, // 17
		64.0, 16.0, 8.0, 1, 1,  0.0f,  1.0f,  0.0f, // 18
		0.0, 16.0, 8.0, 0, 1,   0.0f,  1.0f,  0.0f, // 19

		// bottom
		0.0, 0.0, 0.0, 0, 0, 0.0f,  -1.0f,  0.0f, // 20
		64.0, 0.0, 0.0, 1, 0,  0.0f,  -1.0f,  0.0f, // 21
		64.0, 0.0,  8.0, 1, 1,  0.0f,  -1.0f,  0.0f, // 22
		0.0, 0.0,  8.0, 0, 1, 0.0f,  -1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		//0,  1,  2,  0,  2,  3,  // front
		//4,  5,  6,  4,  6,  7,   // right
		//8,  9,  10, 8,  10, 11,  // back
		//12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18 // upper
		/*20, 22, 21, 20, 23, 22 */  // bottom
	};

	cubeup.SetShader(shadowmapShader);
	cubeup.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));
	cubeup.ApplyTexture("Rakcup.png");
	cubeup.VerticesDraw(sizeof(indices));
	cubeup.transform.SetPosition(glm::vec3(-24.0f, 0.5f, 8.0f));
	cubeup.transform.Scale(glm::vec3(1.0f, 1.0f, 1.0f));
}

void Demo::BuildCube2up() // rak jualan 2
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords, normal
		// front
		0.0, 0.0, 0.0, 0, 0, 0.0f,  0.0f,  1.0f, // 0
		64.0, 0.0, 0.0, 1, 0,  0.0f,  0.0f,  1.0f, // 1
		64.0,  16.0, 0.0, 1, 1,  0.0f,  0.0f,  1.0f, // 2
		0.0,  16.0, 0.0, 0, 1, 0.0f,  0.0f,  1.0f, // 3

		 // right
		 64.0,  0.0,  8.0, 0, 0, 1.0f,  0.0f,  0.0f, // 4
		 64.0,  0.0, 0.0, 1, 0, 1.0f,  0.0f,  0.0f, // 5
		 64.0, 16.0, 0.0, 1, 1, 1.0f,  0.0f,  0.0f, // 6
		 64.0, 16.0,  8.0, 0, 1, 1.0f,  0.0f,  0.0f, // 7

		// back
		0.0, 0.0, 8.0, 0, 0, 0.0f,  0.0f,  -1.0f, // 8 
		64.0,  0.0, 8.0, 1, 0, 0.0f,  0.0f,  -1.0f, // 9
		64.0,   16.0, 8.0, 1, 1, 0.0f,  0.0f,  -1.0f, // 10
		0.0,  16.0, 8.0, 0, 1, 0.0f,  0.0f,  -1.0f, // 11

		 // left
		 0.0, 0.0, 8.0, 0, 0, -1.0f,  0.0f,  0.0f, // 12
		 0.0, 0.0,  0.0, 1, 0, -1.0f,  0.0f,  0.0f, // 13
		 0.0,  16.0,  0.0, 1, 1, -1.0f,  0.0f,  0.0f, // 14
		 0.0,  16.0, 8.0, 0, 1, -1.0f,  0.0f,  0.0f, // 15

		// upper
		0.0, 16.0,  0.0, 0, 0,   0.0f,  1.0f,  0.0f, // 16
		64.0, 16.0, 0.0, 1, 0,   0.0f,  1.0f,  0.0f, // 17
		64.0, 16.0, 8.0, 1, 1,  0.0f,  1.0f,  0.0f, // 18
		0.0, 16.0, 8.0, 0, 1,   0.0f,  1.0f,  0.0f, // 19

		// bottom
		0.0, 0.0, 0.0, 0, 0, 0.0f,  -1.0f,  0.0f, // 20
		64.0, 0.0, 0.0, 1, 0,  0.0f,  -1.0f,  0.0f, // 21
		64.0, 0.0,  8.0, 1, 1,  0.0f,  -1.0f,  0.0f, // 22
		0.0, 0.0,  8.0, 0, 1, 0.0f,  -1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		//0,  1,  2,  0,  2,  3,   // front
		//4,  5,  6,  4,  6,  7,   // right
		//8,  9,  10, 8,  10, 11,  // back
		//12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18  // upper
		/*20, 22, 21, 20, 23, 22 */  // bottom
	};

	cube2up.SetShader(shadowmapShader);
	cube2up.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));
	cube2up.ApplyTexture("Rakup.png");
	cube2up.VerticesDraw(sizeof(indices));
	cube2up.transform.SetPosition(glm::vec3(-24.0f, 0.5f, -16.0f));
	cube2up.transform.Scale(glm::vec3(1.0f, 1.0f, 1.0f));
}

void Demo::BuildCube3() // kulkas
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords, normal
		// front
		0.0, 0.0, 0.0, 0, 0, 0.0f,  0.0f,  1.0f, // 0
		8.0, 0.0, 0.0, 1, 0,  0.0f,  0.0f,  1.0f, // 1
		8.0,  16.0, 0.0, 1, 1,  0.0f,  0.0f,  1.0f, // 2
		0.0,  16.0, 0.0, 0, 1, 0.0f,  0.0f,  1.0f, // 3

		 // right
		 8.0,  0.0,  0.0, 0, 0, 1.0f,  0.0f,  0.0f, // 4
		 8.0,  0.0, 64.0, 1, 0, 1.0f,  0.0f,  0.0f, // 5
		 8.0, 16.0, 64.0, 1, 1, 1.0f,  0.0f,  0.0f, // 6
		 8.0, 16.0,  0.0, 0, 1, 1.0f,  0.0f,  0.0f, // 7

		// back
		0.0, 0.0, 64.0, 0, 0, 0.0f,  0.0f,  -1.0f, // 8 
		8.0,  0.0, 64.0, 1, 0, 0.0f,  0.0f,  -1.0f, // 9
		8.0,   16.0, 64.0, 1, 1, 0.0f,  0.0f,  -1.0f, // 10
		0.0,  16.0, 64.0, 0, 1, 0.0f,  0.0f,  -1.0f, // 11

		 // left
		 0.0, 0.0, 64.0, 0, 0, -1.0f,  0.0f,  0.0f, // 12
		 0.0, 0.0,  0.0, 1, 0, -1.0f,  0.0f,  0.0f, // 13
		 0.0,  16.0,  0.0, 1, 1, -1.0f,  0.0f,  0.0f, // 14
		 0.0,  16.0, 64.0, 0, 1, -1.0f,  0.0f,  0.0f, // 15

		// upper
		0.0, 16.0,  0.0, 0, 0,   0.0f,  1.0f,  0.0f, // 16
		8.0, 16.0, 0.0, 1, 0,   0.0f,  1.0f,  0.0f, // 17
		8.0, 16.0, 64.0, 1, 1,  0.0f,  1.0f,  0.0f, // 18
		0.0, 16.0, 64.0, 0, 1,   0.0f,  1.0f,  0.0f, // 19

		// bottom
		0.0, 0.0, 0.0, 0, 0, 0.0f,  -1.0f,  0.0f, // 20
		8.0, 0.0, 0.0, 1, 0,  0.0f,  -1.0f,  0.0f, // 21
		8.0, 0.0,  64.0, 1, 1,  0.0f,  -1.0f,  0.0f, // 22
		0.0, 0.0,  64.0, 0, 1, 0.0f,  -1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		/*0,  1,  2,  0,  2,  3, */  // front
		/*4,  5,  6,  4,  6,  7 */ // right
		//8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		//16, 18, 17, 16, 19, 18,  // upper
		//20, 22, 21, 20, 23, 22   // bottom
	};

	cube3.SetShader(shadowmapShader);
	cube3.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));

	cube3.ApplyTexture("Kulkas.png");
	cube3.VerticesDraw(sizeof(indices));
	cube3.transform.SetPosition(glm::vec3(64.0f, 0.5f, -32.0f));
	cube3.transform.Scale(glm::vec3(1.0f, 1.0f, 1.0f));
}

void Demo::BuildCube3up() // kulkas
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords, normal
		// front
		0.0, 0.0, 0.0, 0, 0, 0.0f,  0.0f,  1.0f, // 0
		8.0, 0.0, 0.0, 1, 0,  0.0f,  0.0f,  1.0f, // 1
		8.0,  16.0, 0.0, 1, 1,  0.0f,  0.0f,  1.0f, // 2
		0.0,  16.0, 0.0, 0, 1, 0.0f,  0.0f,  1.0f, // 3

		 // right
		 8.0,  0.0,  0.0, 0, 0, 1.0f,  0.0f,  0.0f, // 4
		 8.0,  0.0, 64.0, 1, 0, 1.0f,  0.0f,  0.0f, // 5
		 8.0, 16.0, 64.0, 1, 1, 1.0f,  0.0f,  0.0f, // 6
		 8.0, 16.0,  0.0, 0, 1, 1.0f,  0.0f,  0.0f, // 7

		// back
		0.0, 0.0, 64.0, 0, 0, 0.0f,  0.0f,  -1.0f, // 8 
		8.0,  0.0, 64.0, 1, 0, 0.0f,  0.0f,  -1.0f, // 9
		8.0,   16.0, 64.0, 1, 1, 0.0f,  0.0f,  -1.0f, // 10
		0.0,  16.0, 64.0, 0, 1, 0.0f,  0.0f,  -1.0f, // 11

		 // left
		 0.0, 0.0, 64.0, 0, 0, -1.0f,  0.0f,  0.0f, // 12
		 0.0, 0.0,  0.0, 1, 0, -1.0f,  0.0f,  0.0f, // 13
		 0.0,  16.0,  0.0, 1, 1, -1.0f,  0.0f,  0.0f, // 14
		 0.0,  16.0, 64.0, 0, 1, -1.0f,  0.0f,  0.0f, // 15

		// upper
		0.0, 16.0,  0.0, 0, 0,   0.0f,  1.0f,  0.0f, // 16
		8.0, 16.0, 0.0, 1, 0,   0.0f,  1.0f,  0.0f, // 17
		8.0, 16.0, 64.0, 1, 1,  0.0f,  1.0f,  0.0f, // 18
		0.0, 16.0, 64.0, 0, 1,   0.0f,  1.0f,  0.0f, // 19

		// bottom
		0.0, 0.0, 0.0, 0, 0, 0.0f,  -1.0f,  0.0f, // 20
		8.0, 0.0, 0.0, 1, 0,  0.0f,  -1.0f,  0.0f, // 21
		8.0, 0.0,  64.0, 1, 1,  0.0f,  -1.0f,  0.0f, // 22
		0.0, 0.0,  64.0, 0, 1, 0.0f,  -1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		/*12, 14, 13, 12, 15, 14,*/  // left
		16, 18, 17, 16, 19, 18,// upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	cube3up.SetShader(shadowmapShader);
	cube3up.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));
	cube3up.ApplyTexture("Kulkasside.png");
	cube3up.VerticesDraw(sizeof(indices));
	cube3up.transform.SetPosition(glm::vec3(64.0f, 0.5f, -32.0f));
	cube3up.transform.Scale(glm::vec3(1.0f, 1.0f, 1.0f));
}

void Demo::BuildCube4() // rak kecil
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords, normal
		// front
		0.0, 0.0, 0.0, 0, 0, 0.0f,  0.0f,  1.0f, // 0
		8.0, 0.0, 0.0, 1, 0,  0.0f,  0.0f,  1.0f, // 1
		8.0,  16.0, 0.0, 1, 1,  0.0f,  0.0f,  1.0f, // 2
		0.0,  16.0, 0.0, 0, 1, 0.0f,  0.0f,  1.0f, // 3

		 // right
		 8.0,  0.0,  0.0, 0, 0, 1.0f,  0.0f,  0.0f, // 4
		 8.0,  0.0, 8.0, 1, 0, 1.0f,  0.0f,  0.0f, // 5
		 8.0, 16.0, 8.0, 1, 1, 1.0f,  0.0f,  0.0f, // 6
		 8.0, 16.0,  0.0, 0, 1, 1.0f,  0.0f,  0.0f, // 7

		// back
		0.0, 0.0, 8.0, 0, 0, 0.0f,  0.0f,  -1.0f, // 8 
		8.0,  0.0, 8.0, 1, 0, 0.0f,  0.0f,  -1.0f, // 9
		8.0,   16.0, 8.0, 1, 1, 0.0f,  0.0f,  -1.0f, // 10
		0.0,  16.0, 8.0, 0, 1, 0.0f,  0.0f,  -1.0f, // 11

		 // left
		 0.0, 0.0, 8.0, 0, 0, -1.0f,  0.0f,  0.0f, // 12
		 0.0, 0.0,  0.0, 1, 0, -1.0f,  0.0f,  0.0f, // 13
		 0.0,  16.0,  0.0, 1, 1, -1.0f,  0.0f,  0.0f, // 14
		 0.0,  16.0, 8.0, 0, 1, -1.0f,  0.0f,  0.0f, // 15

		// upper
		0.0, 16.0,  0.0, 0, 0,   0.0f,  1.0f,  0.0f, // 16
		8.0, 16.0, 0.0, 1, 0,   0.0f,  1.0f,  0.0f, // 17
		8.0, 16.0, 8.0, 1, 1,  0.0f,  1.0f,  0.0f, // 18
		0.0, 16.0, 8.0, 0, 1,   0.0f,  1.0f,  0.0f, // 19

		// bottom
		0.0, 0.0, 0.0, 0, 0, 0.0f,  -1.0f,  0.0f, // 20
		8.0, 0.0, 0.0, 1, 0,  0.0f,  -1.0f,  0.0f, // 21
		8.0, 0.0,  8.0, 1, 1,  0.0f,  -1.0f,  0.0f, // 22
		0.0, 0.0,  8.0, 0, 1, 0.0f,  -1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		/*16, 18, 17, 16, 19, 18, */ // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	cube4.SetShader(shadowmapShader);
	cube4.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));

	cube4.ApplyTexture("magazinerack.png");
	cube4.VerticesDraw(sizeof(indices));
	cube4.transform.SetPosition(glm::vec3(-48.0f, 0.5f, -8.0f));
	cube4.transform.Scale(glm::vec3(1.0f, 1.0f, 1.0f));
}

void Demo::BuildCube4up() // rak kecil
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords, normal
		// front
		0.0, 0.0, 0.0, 0, 0, 0.0f,  0.0f,  1.0f, // 0
		8.0, 0.0, 0.0, 1, 0,  0.0f,  0.0f,  1.0f, // 1
		8.0,  16.0, 0.0, 1, 1,  0.0f,  0.0f,  1.0f, // 2
		0.0,  16.0, 0.0, 0, 1, 0.0f,  0.0f,  1.0f, // 3

		 // right
		 8.0,  0.0,  0.0, 0, 0, 1.0f,  0.0f,  0.0f, // 4
		 8.0,  0.0, 8.0, 1, 0, 1.0f,  0.0f,  0.0f, // 5
		 8.0, 16.0, 8.0, 1, 1, 1.0f,  0.0f,  0.0f, // 6
		 8.0, 16.0,  0.0, 0, 1, 1.0f,  0.0f,  0.0f, // 7

		// back
		0.0, 0.0, 8.0, 0, 0, 0.0f,  0.0f,  -1.0f, // 8 
		8.0,  0.0, 8.0, 1, 0, 0.0f,  0.0f,  -1.0f, // 9
		8.0,   16.0, 8.0, 1, 1, 0.0f,  0.0f,  -1.0f, // 10
		0.0,  16.0, 8.0, 0, 1, 0.0f,  0.0f,  -1.0f, // 11

		 // left
		 0.0, 0.0, 8.0, 0, 0, -1.0f,  0.0f,  0.0f, // 12
		 0.0, 0.0,  0.0, 1, 0, -1.0f,  0.0f,  0.0f, // 13
		 0.0,  16.0,  0.0, 1, 1, -1.0f,  0.0f,  0.0f, // 14
		 0.0,  16.0, 8.0, 0, 1, -1.0f,  0.0f,  0.0f, // 15

		// upper
		0.0, 16.0,  0.0, 0, 0,   0.0f,  1.0f,  0.0f, // 16
		8.0, 16.0, 0.0, 1, 0,   0.0f,  1.0f,  0.0f, // 17
		8.0, 16.0, 8.0, 1, 1,  0.0f,  1.0f,  0.0f, // 18
		0.0, 16.0, 8.0, 0, 1,   0.0f,  1.0f,  0.0f, // 19

		// bottom
		0.0, 0.0, 0.0, 0, 0, 0.0f,  -1.0f,  0.0f, // 20
		8.0, 0.0, 0.0, 1, 0,  0.0f,  -1.0f,  0.0f, // 21
		8.0, 0.0,  8.0, 1, 1,  0.0f,  -1.0f,  0.0f, // 22
		0.0, 0.0,  8.0, 0, 1, 0.0f,  -1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		//0,  1,  2,  0,  2,  3,   // front
		//4,  5,  6,  4,  6,  7,   // right
		//8,  9,  10, 8,  10, 11,  // back
		//12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18 // upper
		/*20, 22, 21, 20, 23, 22 */  // bottom
	};

	cube4up.SetShader(shadowmapShader);
	cube4up.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));

	cube4up.ApplyTexture("Wood.png");
	cube4up.VerticesDraw(sizeof(indices));
	cube4up.transform.SetPosition(glm::vec3(-48.0f, 0.5f, -8.0f));
	cube4up.transform.Scale(glm::vec3(1.0f, 1.0f, 1.0f));
}

void Demo::BuildCube5() //kasir
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords, normal
		// front
		0.0, 0.0, 0.0, 0, 0, 0.0f,  0.0f,  1.0f, // 0
		8.0, 0.0, 0.0, 1, 0,  0.0f,  0.0f,  1.0f, // 1
		8.0,  4.0, 0.0, 1, 1,  0.0f,  0.0f,  1.0f, // 2
		0.0,  4.0, 0.0, 0, 1, 0.0f,  0.0f,  1.0f, // 3

		 // right
		 8.0,  0.0,  0.0, 0, 0, 1.0f,  0.0f,  0.0f, // 4
		 8.0,  0.0, 32.0, 1, 0, 1.0f,  0.0f,  0.0f, // 5
		 8.0, 4.0, 32.0, 1, 1, 1.0f,  0.0f,  0.0f, // 6
		 8.0, 4.0,  0.0, 0, 1, 1.0f,  0.0f,  0.0f, // 7

		// back
		0.0, 0.0, 32.0, 0, 0, 0.0f,  0.0f,  -1.0f, // 8 
		8.0,  0.0, 32.0, 1, 0, 0.0f,  0.0f,  -1.0f, // 9
		8.0,   4.0, 32.0, 1, 1, 0.0f,  0.0f,  -1.0f, // 10
		0.0,  4.0, 32.0, 0, 1, 0.0f,  0.0f,  -1.0f, // 11

		 // left
		 0.0, 0.0, 32.0, 0, 0, -1.0f,  0.0f,  0.0f, // 12
		 0.0, 0.0,  0.0, 1, 0, -1.0f,  0.0f,  0.0f, // 13
		 0.0,  4.0,  0.0, 1, 1, -1.0f,  0.0f,  0.0f, // 14
		 0.0,  4.0, 32.0, 0, 1, -1.0f,  0.0f,  0.0f, // 15

		// upper
		0.0, 4.0,  0.0, 0, 0,   0.0f,  1.0f,  0.0f, // 16
		8.0, 4.0, 0.0, 1, 0,   0.0f,  1.0f,  0.0f, // 17
		8.0, 4.0, 32.0, 1, 1,  0.0f,  1.0f,  0.0f, // 18
		0.0, 4.0, 32.0, 0, 1,   0.0f,  1.0f,  0.0f, // 19

		// bottom
		0.0, 0.0, 0.0, 0, 0, 0.0f,  -1.0f,  0.0f, // 20
		8.0, 0.0, 0.0, 1, 0,  0.0f,  -1.0f,  0.0f, // 21
		8.0, 0.0,  32.0, 1, 1,  0.0f,  -1.0f,  0.0f, // 22
		0.0, 0.0,  32.0, 0, 1, 0.0f,  -1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	cube5.SetShader(shadowmapShader);
	cube5.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));

	cube5.ApplyTexture("Kasir.png");
	cube5.VerticesDraw(sizeof(indices));
	cube5.transform.SetPosition(glm::vec3(-48.0f, 4.0f, 0.0f));
	cube5.transform.Scale(glm::vec3(1.0f, 1.0f, 1.0f));
}

void Demo::BuildCube6()
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords, normal
		// front
		0.0, 0.0, 0.0, 0, 0, 0.0f,  0.0f,  1.0f, // 0
		128.0, 0.0, 0.0, 1, 0,  0.0f,  0.0f,  1.0f, // 1
		128.0,  40.0, 0.0, 1, 1,  0.0f,  0.0f,  1.0f, // 2
		0.0,  40.0, 0.0, 0, 1, 0.0f,  0.0f,  1.0f, // 3

		 // right
		 128.0,  0.0,  0.0, 0, 0, 1.0f,  0.0f,  0.0f, // 4
		 128.0,  0.0, 64.0, 1, 0, 1.0f,  0.0f,  0.0f, // 5
		 128.0, 40.0, 64.0, 1, 1, 1.0f,  0.0f,  0.0f, // 6
		 128.0, 40.0,  0.0, 0, 1, 1.0f,  0.0f,  0.0f, // 7

		// back
		0.0, 0.0, 64.0, 0, 0, 0.0f,  0.0f,  -1.0f, // 8 
		128.0,  0.0, 64.0, 1, 0, 0.0f,  0.0f,  -1.0f, // 9
		128.0,   40.0, 64.0, 1, 1, 0.0f,  0.0f,  -1.0f, // 10
		0.0,  40.0, 64.0, 0, 1, 0.0f,  0.0f,  -1.0f, // 11

		 // left
		 0.0, 0.0, 64.0, 0, 0, -1.0f,  0.0f,  0.0f, // 12
		 0.0, 0.0,  0.0, 1, 0, -1.0f,  0.0f,  0.0f, // 13
		 0.0,  40.0,  0.0, 1, 1, -1.0f,  0.0f,  0.0f, // 14
		 0.0,  40.0, 64.0, 0, 1, -1.0f,  0.0f,  0.0f, // 15

		// upper
		0.0, 40.0,  0.0, 0, 0,   0.0f,  1.0f,  0.0f, // 16
		128.0, 40.0, 0.0, 1, 0,   0.0f,  1.0f,  0.0f, // 17
		128.0, 40.0, 64.0, 1, 1,  0.0f,  1.0f,  0.0f, // 18
		0.0, 40.0, 64.0, 0, 1,   0.0f,  1.0f,  0.0f, // 19

		// bottom
		0.0, 0.0, 0.0, 0, 0, 0.0f,  -1.0f,  0.0f, // 20
		128.0, 0.0, 0.0, 1, 0,  0.0f,  -1.0f,  0.0f, // 21
		128.0, 0.0,  64.0, 1, 1,  0.0f,  -1.0f,  0.0f, // 22
		0.0, 0.0,  64.0, 0, 1, 0.0f,  -1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	cube6.SetShader(shadowmapShader);
	cube6.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));

	cube6.ApplyTexture("Floor.png");
	cube6.VerticesDraw(sizeof(indices));
	cube6.transform.SetOrigin(glm::vec3(0.0f, 0.0f, 0.0f));
	cube6.transform.SetPosition(glm::vec3(-56.0f, 0.0f, -32.0f));
	cube6.transform.Scale(glm::vec3(1.0f, 1.0f, 1.0f));
}

void Demo::ApplyTexture(const char* _texturePath)
{
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("crate.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Demo::BuildObject(float* _vertices, size_t verticesSize, unsigned int* _indices, size_t indicesSize)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSize, _vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, _indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// define normal pointer layout 2
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Demo::DrawTexturedCube(GLuint shader)
{
	this->shader.UseShader(shader);
	glBindVertexArray(VAO);
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0, 0.5f, 0));

	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildTexturedPlane()
{
	// Load and create a texture 
	glGenTextures(1, &plane_texture);
	glBindTexture(GL_TEXTURE_2D, plane_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("Floor.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);


	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		-100.0f,	-0.5f, -100.0f,  0,  0, 0.0f,  1.0f,  0.0f,
		100.0f,	-0.5f, -100.0f, 100,  0, 0.0f,  1.0f,  0.0f,
		100.0f,	-0.5f,  100.0f, 100, 100, 0.0f,  1.0f,  0.0f,
		-100.0f,	-0.5f,  100.0f,  0, 100, 0.0f,  1.0f,  0.0f,
	};

	GLuint indices[] = { 0,  2,  1,  0,  3,  2 };

	glGenVertexArrays(1, &planeVAO);
	glGenBuffers(1, &planeVBO);
	glGenBuffers(1, &planeEBO);

	glBindVertexArray(planeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planeEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Normal attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}

void Demo::DrawTexturedPlane(GLuint shader)
{
	this->shader.UseShader(shader);
	glBindVertexArray(planeVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(shader, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildDepthMap() {
	// configure depth map FBO
	// -----------------------
	glGenFramebuffers(1, &depthMapFBO);
	// create depth texture
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, this->SHADOW_WIDTH, this->SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void Demo::BuildShaders()
{
	// build and compile our shader program
	// ------------------------------------
	shadowmapShader = shader.GetBuildShader("shadowMapping.vert", "shadowMapping.frag", nullptr);
	depthmapShader = shader.GetBuildShader("depthMap.vert", "depthMap.frag", nullptr);
}

int main(int argc, char** argv) {
	RenderEngine &app = Demo();
	app.Start("Shadow Mapping Demo", 800, 600, false, true);
}