#pragma once

#include <vector>
#include "ShaderManager.h"
#include "Object.h"
#include "Camera.h"
#include "CameraOrbitControl.h"

class Scene {
private:
	int width, height;
	GLFWwindow* window;
	std::vector<Object> objects;
	bool firstClick = true;
	double firstX, firstY;

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{

		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);

		static_cast<Scene*>(glfwGetWindowUserPointer(window))->keybord_event(action, key);
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

	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		static_cast<Scene*>(glfwGetWindowUserPointer(window))->wheel_update(yoffset);
	}

	void SetInputEvent() {
		//set window pointer before get in input event
		glfwSetWindowUserPointer(window, this);

		glfwSetKeyCallback(window, key_callback);
		glfwSetCursorPosCallback(window, cursor_position_callback);
		glfwSetScrollCallback(window, scroll_callback);
	}

public:
	Camera camera;
	Object triangle, cube;
	CameraOrbitControl orbitControl;
	bool showPos = false;
	Scene() {

	}

	Scene(GLFWwindow* _window, int _width, int _height)
		:window(_window), width(_width), height(_height)
	{
		SetInputEvent();
	}

	~Scene() {

	}

	void SetSceneSize(int _width, int _height) { width = _width; height = _height; }
	void SetWindow(GLFWwindow* _window) {
		window = _window;

		SetInputEvent();
	}

	GLFWwindow* GetWindow() { return window; }

	void start();
	void update();
	void destroy();
	void keybord_event(int action, int key);
	void cursor_position_update(double xpos, double ypos);
	void mouse_button_clicked(int button, int mods);
	void wheel_update( double offset);
};

