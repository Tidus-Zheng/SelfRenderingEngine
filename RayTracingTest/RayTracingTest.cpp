#include "linmath.h"

#include "Utility.h"
#include "ShaderManager.h"
#include "Object.h"
#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include "Scene.h"
#include "RayTracingTest.h"


static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

//keybord event
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (action == GLFW_RELEASE)
		scene.key_up(key);
}

//mouse position event;
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	scene.cursor_position_update(xpos, ypos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	scene.mouse_button_clicked(button, mods);
}

int main(void)
{
	GLFWwindow* window;
	GLint mvp_location, vpos_location, vcol_location;
	ShaderManger simpleShader;

	int width = 640;
	int height = 480;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(width, height, "Simple example", NULL, NULL);
	scene.SetSceneSize(width, height);
	scene.SetWindow(window);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	scene.start();

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);
	glfwSwapInterval(0); //1: 60fps, 0:unlimit

	simpleShader.init("vertex.vs", "fragment.fs");

	mvp_location = simpleShader.GetUniformLocation("MVP");
	vpos_location = simpleShader.GetAttribLocation("vPos");
	vcol_location = simpleShader.GetAttribLocation("vCol");

	//create object and pass to vertex buffer
	std::vector<glm::vec3> triVer, triCol;
	triVer.push_back(glm::vec3(-0.6f, -0.4f, -1.f));
	triVer.push_back(glm::vec3(0.6f, -0.4f, -1.f));
	triVer.push_back(glm::vec3(0.f, 0.6f, -1.f));

	triCol.push_back(glm::vec3(1.f, 0.f, 0.f));
	triCol.push_back(glm::vec3(0.f, 1.f, 0.f));
	triCol.push_back(glm::vec3(0.f, 0.f, 1.f));

	Object triangle(triVer, triCol);
	triangle.AttributeVertices(vpos_location);
	triangle.AttributeColors(vcol_location);

	float currentTime = static_cast<float>(glfwGetTime());
	float lastFramesPrint = currentTime;
	float frameCount = 0;

	while (!glfwWindowShouldClose(window))
	{
		scene.update();
		//check fps
		frameCount++;
		float newTime = static_cast<float>(glfwGetTime());
		float deltaTime = newTime - currentTime;
		currentTime = newTime;

		if (newTime - lastFramesPrint > 1.0f) {
			std::cout << "FPS: " << frameCount << std::endl;
			lastFramesPrint = newTime;
			frameCount = 0;
		}

		float ratio;
		//int width, height;
		mat4x4 m, p, mvp;

		//glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		Camera perspecCamera(width, height);

		mat4x4_identity(m);
		mat4x4_rotate_Z(m, m, (float)glfwGetTime());

		perspecCamera.GetMVPMatrix(mvp);
		mat4x4_mul(mvp, mvp, m);

		simpleShader.UseProgram();
		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)mvp);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	scene.destroy();

	glfwTerminate();
	exit(EXIT_SUCCESS);
}