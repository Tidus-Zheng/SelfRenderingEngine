#include "Scene.h"

#define Log(A) std::cout<<#A<<std::endl;


void Scene::start()
{
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
}

void Scene::update()
{
	float ratio;
	//int width, height;
	mat4x4 m, p, mvp;

	//glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);

	Camera perspecCamera(width, height);

	mat4x4_identity(m);
	mat4x4_rotate_Z(m, m, (float)glfwGetTime());

	perspecCamera.GetMVPMatrix(mvp);
	mat4x4_mul(mvp, mvp, m);

	simpleShader.UseProgram();
	glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)mvp);
	glDrawArrays(GL_TRIANGLES, 0, 3);

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
