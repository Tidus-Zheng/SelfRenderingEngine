#include "Scene.h"
#include "ShaderManager.h"
#include "Object.h"

#define Log(A) std::cout<<#A<<std::endl;

void Scene::start()
{

}

void Scene::update()
{
}

void Scene::destroy()
{
}

void Scene::key_up(int key)
{
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

void Scene::cursor_position_update(double xpos, double ypos)
{
}

void Scene::mouse_button_clicked(int button, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
		Log(Right_Button_Click);
}
