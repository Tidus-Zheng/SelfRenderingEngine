#include "linmath.h"

#include "Utility.h"
#include "ShaderManager.h"
#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include "Scene.h"


static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}


int main(void)
{
	GLFWwindow* window;
	int width = 640;
	int height = 480;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//enable depth buffer
	//glfwWindowHint(GLFW_DEPTH_BITS, GL_TRUE);


	window = glfwCreateWindow(width, height, "Simple example", NULL, NULL);

	Scene scene(window, width, height);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);
	glfwSwapInterval(1); //1: 60fps, 0:unlimit

	scene.start();

	float currentTime = static_cast<float>(glfwGetTime());
	float lastFramesPrint = currentTime;
	float frameCount = 0;

	while (!glfwWindowShouldClose(window))
	{
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

		scene.update();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	scene.destroy();

	glfwTerminate();
	exit(EXIT_SUCCESS);
}