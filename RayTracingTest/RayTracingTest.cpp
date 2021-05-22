#include "linmath.h"

#include "Utility.h"
#include "ShaderManager.h"
#include "Object.h"
#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>

#define Log(A) std::cout<<#A<<std::endl;

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	switch (key) {
	case GLFW_KEY_W:
		Log(w);
		break;
	case GLFW_KEY_S:
		Log(s);
		break;
	case GLFW_KEY_A:
		Log(a);
		break;
	case GLFW_KEY_D:
		Log(d);
		break;
	default:
		break;
	}
}

int main(void)
{
	GLFWwindow* window;
	GLint mvp_location, vpos_location, vcol_location;
	ShaderManger simpleShader;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);

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
		int width, height;
		mat4x4 m, p, mvp;

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		Camera perspecCamera(width, height);
		perspecCamera.UpdatePosition(glm::vec3(0, glfwGetTime() * 0.1f, 0));

		mat4x4_identity(m);
		mat4x4_rotate_Z(m, m, (float)glfwGetTime());
		////mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		//mat4x4_perspective(p, height, ratio, 0.1, 1000);
		//mat4x4_mul(mvp, p, m);
		perspecCamera.GetMVPMatrix(mvp);
		mat4x4_mul(mvp, mvp, m);

		simpleShader.UseProgram();
		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)mvp);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}