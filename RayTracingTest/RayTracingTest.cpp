#include "linmath.h"

#include "Utility.h"
#include "ShaderManager.h"
#include <glm/gtc/type_ptr.hpp>
#include "Scene.h"

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}


int main(void)
{
	GLFWwindow* window;
	int width = 1280;
	int height = 720;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//enable depth buffer
	glfwWindowHint(GLFW_DEPTH_BITS, GL_TRUE);

	window = glfwCreateWindow(width, height, "Simple example", NULL, NULL);

	//Scene* scene = new Scene(window, width, height);
	//Scene* scene = new Scene();
	//scene->SetWindow(window);
	//scene->SetSceneSize(width, height);
	Scene::Instance().SetWindow(window);
	Scene::Instance().SetSceneSize(width, height);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);
	glfwSwapInterval(1); //1: 60fps, 0:unlimit

	//scene->start();
	Scene::Instance().start();

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

		Scene::Instance().update();

		//window resize
		int newWidth = width, newHeight = height;
		glfwGetWindowSize(window, &newWidth, &newHeight);
		if (newWidth != width || newHeight != height) {
			glfwSetWindowSize(window, newWidth, newHeight);
			Scene::Instance().SetSceneSize(newWidth, newHeight);
			width = newWidth;
			height = newHeight;
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	Scene::Instance().destroy();
	//delete scene;

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
