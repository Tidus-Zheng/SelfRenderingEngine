#include "Scene.h"

#define Log(A) std::cout<<#A<<std::endl;


void Scene::start()
{
	camera.SetResulution(width, height);
	//camera.SetPosition(glm::vec3(1, 1, 1));
	orbitControl.SetCamera(&camera);
	simpleShader.init("vertex.vs", "fragment.fs");

	//create object and pass to vertex buffer
	std::vector<glm::vec3> triVer, triCol;
	triVer.push_back(glm::vec3(-0.6f, -0.4f, 0.f));
	triVer.push_back(glm::vec3(0.6f, -0.4f, 0.f));
	triVer.push_back(glm::vec3(0.f, 0.6f, 0.f));

	triCol.push_back(glm::vec3(1.f, 0.f, 0.f));
	triCol.push_back(glm::vec3(0.f, 1.f, 0.f));
	triCol.push_back(glm::vec3(0.f, 0.f, 1.f));

	triangle.SetVertices(triVer);
	triangle.SetColors(triCol);

	triangle.AttributeVertices(&simpleShader, "vPos");
	triangle.AttributeColors(&simpleShader, "vCol");

	triangle.position.z = -2;
}

void Scene::update()
{
	mat4x4 model, view, proj;

	//glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//back face culling
	//glEnable(GL_CULL_FACE);

	triangle.rotation.z = (float)glfwGetTime();

	triangle.GetModelMatrix(model);
	camera.GetViewMatrix(view);
	camera.GetProjMatrix(proj);

	simpleShader.UseProgram();
	glUniformMatrix4fv(simpleShader.GetUniformLocation("model"), 1, GL_FALSE, (const GLfloat*)model);
	glUniformMatrix4fv(simpleShader.GetUniformLocation("view"), 1, GL_FALSE, (const GLfloat*)view);
	glUniformMatrix4fv(simpleShader.GetUniformLocation("proj"), 1, GL_FALSE, (const GLfloat*)proj);
	triangle.Draw();
}

void Scene::destroy()
{
}

void Scene::keybord_event(int action, int key)
{
	if (action == GLFW_REPEAT || action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_W:
			orbitControl.Move(glm::vec3(0.f, 0.f, -0.1f));
			break;
		case GLFW_KEY_S:
			orbitControl.Move(glm::vec3(0.f, 0.f, 0.1f));
			break;
		case GLFW_KEY_A:
			orbitControl.Move(glm::vec3(-0.1f, 0.f, 0.f));
			break;
		case GLFW_KEY_D:
			orbitControl.Move(glm::vec3(0.1f, 0.f, 0.f));
			break;
		case GLFW_KEY_SPACE:
			orbitControl.Move(glm::vec3(0.0f, 0.1f, 0.0f));
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
		//upgrade_cow();
		//std::cout << "left press" << std::endl;
	}

	if (state == GLFW_RELEASE) {
		firstClick = true;
		//std::cout << "left up" << std::endl;
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
