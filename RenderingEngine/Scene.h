#pragma once

#include <vector>
#include "ShaderManager.h"
#include "Camera.h"
#include "CameraOrbitControl.h"
#include "Mesh.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "Model.h"

class Scene final{
private:
	int width, height;
	GLFWwindow* window;
	bool firstClick = true;
	double firstX, firstY;

	Scene();
	~Scene() {
		delete camera;
	}

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{

		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);

		Scene::Instance().keybord_event(action, key);
	}

	//mouse position event;
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Scene::Instance().cursor_position_update(xpos, ypos);
	}

	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		Scene::Instance().mouse_button_clicked(button, mods);
	}

	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		Scene::Instance().wheel_update(yoffset);
	}

	void SetInputEvent() {
		//set window pointer before get in input event
		glfwSetWindowUserPointer(window, this);

		glfwSetKeyCallback(window, key_callback);
		glfwSetCursorPosCallback(window, cursor_position_callback);
		glfwSetScrollCallback(window, scroll_callback);
	}

public:
	Camera* camera;
	CameraOrbitControl orbitControl;
	DirectionalLight directionLight;

	Model model;
	Model model2;

	//Mesh cubeMesh;

	bool showPos = false;

	static Scene& Instance();
	//Scene(GLFWwindow* _window, int _width, int _height)
	//	:window(_window), width(_width), height(_height)
	//{
	//	SetInputEvent();
	//}

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
	void wheel_update(double offset);
};
