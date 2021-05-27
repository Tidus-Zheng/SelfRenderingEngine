#pragma once

#include <vector>
#include "ShaderManager.h"
#include "Object.h"
#include "Camera.h"

class Scene {
private:
	int width, height;
	GLFWwindow* window;
	std::vector<Object> objects;

public:
	Camera camera;
	ShaderManger simpleShader;
	GLint mvp_location, vpos_location, vcol_location;

	Scene() {

	}

	Scene(GLFWwindow* _window, int _width, int _height)
		:window(_window), width(_width), height(_height)
	{

	}

	~Scene() {

	}

	void SetSceneSize(int _width, int _height) { width = _width; height = _height; }
	void SetWindow(GLFWwindow* _window) {
		window = _window;

		glfwSetKeyCallback(window, key_callback);
		glfwSetCursorPosCallback(window, cursor_position_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
	}

	//keybord event
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);

		if (action == GLFW_RELEASE)
			static_cast<Scene*>(glfwGetWindowUserPointer(window))->key_up(key);
	}

	//mouse position event;
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		static_cast<Scene*>(glfwGetWindowUserPointer(window))->cursor_position_update(xpos, ypos);
	}

	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		static_cast<Scene*>(glfwGetWindowUserPointer(window))->mouse_button_clicked(button, mods);
	}

	GLFWwindow* GetWindow() { return window; }

	void start();
	void update();
	void destroy();
	void key_up(int key);
	void cursor_position_update(double xpos, double ypos);
	void mouse_button_clicked(int button, int mods);
};

