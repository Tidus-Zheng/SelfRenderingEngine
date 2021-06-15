#include "Scene.h"

#define Log(A) std::cout<<#A<<std::endl;


void Scene::start()
{
	simpleShader.init("vertex.vs", "fragment.fs");
	camera.SetResulution(width, height);
	orbitControl.SetCamera(&camera);

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices = { 0,1,2 ,3,4,5 };
	Vertex v1;
	v1.position = glm::vec3(-1.f, 1.f, 1.f);
	v1.normal = glm::vec3(0.f, 0.f, 1.f);
	v1.uv = glm::vec2(0.0f, 0.f);
	vertices.push_back(v1);

	Vertex v2;
	v2.position = glm::vec3(-1.f, -1.f, 1.f);
	v2.normal = glm::vec3(0.f, 0.f, 1.f);
	v2.uv = glm::vec2(0.f, 1.f);
	vertices.push_back(v2);

	Vertex v3;
	v3.position = glm::vec3(1.f, -1.f, 1.f);
	v3.normal = glm::vec3(0.f, 0.f, 1.f);
	v3.uv = glm::vec2(1.f, 1.f);
	vertices.push_back(v3);

	Vertex v4;
	v4.position = glm::vec3(-1.f, 1.f, 1.f);
	v4.normal = glm::vec3(0.f, 0.f, 1.f);
	v4.uv = glm::vec2(0.f, 0.f);
	vertices.push_back(v4);

	Vertex v5;
	v5.position = glm::vec3(1.f, -1.f, 1.f);
	v5.normal = glm::vec3(0.f, 0.f, 1.f);
	v5.uv = glm::vec2(1.f, 1.f);
	vertices.push_back(v5);

	Vertex v6;
	v6.position = glm::vec3(1.f, 1.f, 1.f);
	v6.normal = glm::vec3(0.f, 0.f, 1.f);
	v6.uv = glm::vec2(1.f, 0.f);
	vertices.push_back(v6);

	string path = "E:/ray tracing/ray-tracing/x64/Debug/image.png";
	Texture tex(path);
	tex.type = diffuse;
	Mesh mesh(vertices, indices, { tex });
	meshes.push_back(mesh);
}

void Scene::update()
{
	//glfwGetFramebufferSize(window, &width, &height);
	mat4x4 model, view, proj;

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//back face culling
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	//cube.rotation.x = glfwGetTime();
	//cube.rotation.z = glfwGetTime()/2;
	//cube.Render(&camera);

	//triangle.rotation.z = glfwGetTime();
	//triangle.Render(&camera);
	simpleShader.UseProgram();
	mat4x4_identity(model);
	camera.GetViewMatrix(view);
	camera.GetProjMatrix(proj);
	glUniformMatrix4fv(simpleShader.GetUniformLocation("model"), 1, GL_FALSE, (const GLfloat*)model);
	glUniformMatrix4fv(simpleShader.GetUniformLocation("view"), 1, GL_FALSE, (const GLfloat*)view);
	glUniformMatrix4fv(simpleShader.GetUniformLocation("proj"), 1, GL_FALSE, (const GLfloat*)proj);
	for (int i = 0; i < meshes.size(); i++) {
		meshes[i].Draw(simpleShader);
	}
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
			orbitControl.Move(glm::vec3(-1.f, 0.f, 0.f));
			break;
		case GLFW_KEY_D:
			orbitControl.Move(glm::vec3(1.f, 0.f, 0.f));
			break;
		case GLFW_KEY_T:
			showPos = !showPos;
			break;
		case GLFW_KEY_SPACE:
			orbitControl.Move(glm::vec3(0.0f, 1.f, 0.0f));
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
