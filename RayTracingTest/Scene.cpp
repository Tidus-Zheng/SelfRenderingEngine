#include "Scene.h"

#define Log(A) std::cout<<#A<<std::endl;


void Scene::start()
{
	camera.SetResulution(width, height);

	simpleShader.init("vertex.vs", "fragment.fs");

	//create object and pass to vertex buffer
	std::vector<glm::vec3> triVer, triCol;
	triVer.push_back(glm::vec3(-0.6f, -0.4f, 0.f));
	triVer.push_back(glm::vec3(0.6f, -0.4f, 0.f));
	triVer.push_back(glm::vec3(0.f, 0.6f, 0.f));

	triCol.push_back(glm::vec3(1.f, 0.f, 0.f));
	triCol.push_back(glm::vec3(0.f, 1.f, 0.f));
	triCol.push_back(glm::vec3(0.f, 0.f, 1.f));

	Object triangle(triVer, triCol);
	triangle.AttributeVertices(&simpleShader, "vPos");
	triangle.AttributeColors(&simpleShader, "vCol");
}

void Scene::update()
{
	mat4x4 m, p, mvp;

	//glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//back face culling
	glEnable(GL_CULL_FACE);

	mat4x4_identity(m);
	mat4x4_rotate_Z(m, m, (float)glfwGetTime());
	//mat4x4_rotate_Y(m, m, (float)glfwGetTime());

	camera.GetMVPMatrix(mvp);
	mat4x4_mul(mvp, mvp, m);

	simpleShader.UseProgram();
	glUniformMatrix4fv(simpleShader.GetUniformLocation("MVP"), 1, GL_FALSE, (const GLfloat*)mvp);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Scene::destroy()
{
}

void Scene::keybord_event(int action, int key)
{
	if (action == GLFW_REPEAT) {
		switch (key) {
		case GLFW_KEY_W:
			camera.UpdatePosition(glm::vec3(0.f, 0.f, -0.1f));
			break;
		case GLFW_KEY_S:
			camera.UpdatePosition(glm::vec3(0.f, 0.f, 0.1f));
			break;
		case GLFW_KEY_A:
			camera.UpdatePosition(glm::vec3(-0.1f, 0.f, 0.f));
			break;
		case GLFW_KEY_D:
			camera.UpdatePosition(glm::vec3(0.1f, 0.f, 0.f));
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
		//upgrade_cow();
		std::cout << "left press" << std::endl;
	}
}

void Scene::mouse_button_clicked(int button, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		Log(Right_Button_Click);
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT) {
		Log(Left_Button_Click);
	}
}
