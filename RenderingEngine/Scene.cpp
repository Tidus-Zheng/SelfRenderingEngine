#include "Scene.h"

#define Log(A) std::cout<<#A<<std::endl;

Scene::Scene() {

}

Scene& Scene::Instance()
{
	// TODO: insert return statement here
	static Scene instance;
	return instance;
}

void Scene::start()
{
	camera = new Camera();
	camera->SetResulution(width, height);
	camera->SetPosition(glm::vec3(0, 10, 20));
	camera->SetLookAt(glm::vec3(0, 10, 0));
	orbitControl.SetCamera(camera);

	model.LoadModel("E:/model/model/nanosuit.obj");
	model2.LoadModel("E:/model/model/nanosuit.obj");

	model.SetPosition(-5, 0, 0);
	model2.SetPosition(5, 0, 0);
}

void Scene::update()
{
	//glfwGetFramebufferSize(window, &width, &height);
	mat4x4 m, view, proj;
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//back face culling
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
	model.Draw();
	model2.Draw();
}

void Scene::destroy()
{

}

void Scene::keybord_event(int action, int key)
{
	if (action == GLFW_REPEAT || action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_W:
			orbitControl.Move(glm::vec3(0.f, 0.f, -1.f));
			break;
		case GLFW_KEY_S:
			orbitControl.Move(glm::vec3(0.f, 0.f, 1.f));
			break;
		case GLFW_KEY_A:
			orbitControl.Move(glm::vec3(1.f, 0.f, 0.f));
			break;
		case GLFW_KEY_D:
			orbitControl.Move(glm::vec3(-1.f, 0.f, 0.f));
			break;
		case GLFW_KEY_T:
			showPos = !showPos;
			break;
		case GLFW_KEY_SPACE:
			orbitControl.Move(glm::vec3(0.0f, -1.f, 0.0f));
			break;
		default:
			break;
		}
	}
}

void Scene::cursor_position_update(double xpos, double ypos)
{
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

	if (state == GLFW_PRESS)
	{
		if (firstClick) {
			firstX = xpos;
			firstY = ypos;
			firstClick = false;
		}
		orbitControl.Rotate(xpos - firstX, ypos - firstY);

		firstX = xpos;
		firstY = ypos;
	}

	if (state == GLFW_RELEASE) {
		firstClick = true;
	}
}

void Scene::mouse_button_clicked(int button, int mods)
{
	std::cout << mods << std::endl;
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		Log(Right_Button_Click);
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT) {
		Log(Left_Button_Click);
	}
}

void Scene::wheel_update(double offset)
{
	orbitControl.ArmLengthUpdate(-offset);
}
