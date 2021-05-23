#pragma once

#include "Camera.h"

class Scene {
private:
	int width, height;
	GLFWwindow* window;

public:
	Camera camera;

	Scene() {

	}

	Scene(GLFWwindow* _window, int _width, int _height)
		:window(_window), width(_width), height(_height)
	{

	}

	~Scene() {

	}

	void SetSceneSize(int _width, int _height) { width = _width; height = _height; }
	void SetWindow(GLFWwindow* _window) { window = _window; }

	void start();
	void update();
	void destroy();
	void key_up(int key);
	void cursor_position_update(double xpos, double ypos);
	void mouse_button_clicked(int button, int mods);
};