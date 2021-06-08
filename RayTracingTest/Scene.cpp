#include "Scene.h"

#define Log(A) std::cout<<#A<<std::endl;


void Scene::start()
{
	camera.SetResulution(width, height);
	orbitControl.SetCamera(&camera);

	//create object and pass to vertex buffer (CCW)
	std::vector<glm::vec3> cubeVer, cubeCol;
	//front 
	cubeVer.push_back(glm::vec3(-1.f, 1.f, 1.f));
	cubeVer.push_back(glm::vec3(-1.f, -1.f, 1.f));
	cubeVer.push_back(glm::vec3(1.f, -1.f, 1.f));

	cubeVer.push_back(glm::vec3(-1.f, 1.f, 1.f));
	cubeVer.push_back(glm::vec3(1.f, -1.f, 1.f));
	cubeVer.push_back(glm::vec3(1.f, 1.f, 1.f));
	//right
	cubeVer.push_back(glm::vec3(1.f, 1.f, 1.f));
	cubeVer.push_back(glm::vec3(1.f, -1.f, 1.f));
	cubeVer.push_back(glm::vec3(1.f, -1.f, -1.f));

	cubeVer.push_back(glm::vec3(1.f, 1.f, 1.f));
	cubeVer.push_back(glm::vec3(1.f, -1.f, -1.f));
	cubeVer.push_back(glm::vec3(1.f, 1.f, -1.f));
	//back
	cubeVer.push_back(glm::vec3(1.f, 1.f, -1.f));
	cubeVer.push_back(glm::vec3(1.f, -1.f, -1.f));
	cubeVer.push_back(glm::vec3(-1.f, -1.f, -1.f));

	cubeVer.push_back(glm::vec3(1.f, 1.f, -1.f));
	cubeVer.push_back(glm::vec3(-1.f, -1.f, -1.f));
	cubeVer.push_back(glm::vec3(-1.f, 1.f, -1.f));
	//left
	cubeVer.push_back(glm::vec3(-1.f, 1.f, -1.f));
	cubeVer.push_back(glm::vec3(-1.f, -1.f, -1.f));
	cubeVer.push_back(glm::vec3(-1.f, -1.f, 1.f));

	cubeVer.push_back(glm::vec3(-1.f, 1.f, -1.f));
	cubeVer.push_back(glm::vec3(-1.f, -1.f, 1.f));
	cubeVer.push_back(glm::vec3(-1.f, 1.f, 1.f));
	//top
	cubeVer.push_back(glm::vec3(-1.f, 1.f, -1.f));
	cubeVer.push_back(glm::vec3(-1.f, 1.f, 1.f));
	cubeVer.push_back(glm::vec3(1.f, 1.f, 1.f));

	cubeVer.push_back(glm::vec3(-1.f, 1.f, -1.f));
	cubeVer.push_back(glm::vec3(1.f, 1.f, 1.f));
	cubeVer.push_back(glm::vec3(1.f, 1.f, -1.f));
	//bottom
	cubeVer.push_back(glm::vec3(-1.f, -1.f, 1.f));
	cubeVer.push_back(glm::vec3(-1.f, -1.f, -1.f));
	cubeVer.push_back(glm::vec3(1.f, -1.f, -1.f));

	cubeVer.push_back(glm::vec3(-1.f, -1.f, 1.f));
	cubeVer.push_back(glm::vec3(1.f, -1.f, -1.f));
	cubeVer.push_back(glm::vec3(1.f, -1.f, 1.f));

	//front red
	cubeCol.push_back(glm::vec3(1.f, 0.f, 0.f));
	cubeCol.push_back(glm::vec3(1.f, 0.f, 0.f));
	cubeCol.push_back(glm::vec3(1.f, 0.f, 0.f));
	cubeCol.push_back(glm::vec3(1.f, 0.f, 0.f));
	cubeCol.push_back(glm::vec3(1.f, 0.f, 0.f));
	cubeCol.push_back(glm::vec3(1.f, 0.f, 0.f));
	//right green
	cubeCol.push_back(glm::vec3(0.f, 1.f, 0.f));
	cubeCol.push_back(glm::vec3(0.f, 1.f, 0.f));
	cubeCol.push_back(glm::vec3(0.f, 1.f, 0.f));
	cubeCol.push_back(glm::vec3(0.f, 1.f, 0.f));
	cubeCol.push_back(glm::vec3(0.f, 1.f, 0.f));
	cubeCol.push_back(glm::vec3(0.f, 1.f, 0.f));
	//back blue
	cubeCol.push_back(glm::vec3(0.f, 0.f, 1.f));
	cubeCol.push_back(glm::vec3(0.f, 0.f, 1.f));
	cubeCol.push_back(glm::vec3(0.f, 0.f, 1.f));
	cubeCol.push_back(glm::vec3(0.f, 0.f, 1.f));
	cubeCol.push_back(glm::vec3(0.f, 0.f, 1.f));
	cubeCol.push_back(glm::vec3(0.f, 0.f, 1.f));
	//left cyan
	cubeCol.push_back(glm::vec3(0.f, 1.f, 1.f));
	cubeCol.push_back(glm::vec3(0.f, 1.f, 1.f));
	cubeCol.push_back(glm::vec3(0.f, 1.f, 1.f));
	cubeCol.push_back(glm::vec3(0.f, 1.f, 1.f));
	cubeCol.push_back(glm::vec3(0.f, 1.f, 1.f));
	cubeCol.push_back(glm::vec3(0.f, 1.f, 1.f));
	//top yellow
	cubeCol.push_back(glm::vec3(1.f, 1.f, 0.f));
	cubeCol.push_back(glm::vec3(1.f, 1.f, 0.f));
	cubeCol.push_back(glm::vec3(1.f, 1.f, 0.f));
	cubeCol.push_back(glm::vec3(1.f, 1.f, 0.f));
	cubeCol.push_back(glm::vec3(1.f, 1.f, 0.f));
	cubeCol.push_back(glm::vec3(1.f, 1.f, 0.f));
	//bottom magenta
	cubeCol.push_back(glm::vec3(1.f, 0.f, 1.f));
	cubeCol.push_back(glm::vec3(1.f, 0.f, 1.f));
	cubeCol.push_back(glm::vec3(1.f, 0.f, 1.f));
	cubeCol.push_back(glm::vec3(1.f, 0.f, 1.f));
	cubeCol.push_back(glm::vec3(1.f, 0.f, 1.f));
	cubeCol.push_back(glm::vec3(1.f, 0.f, 1.f));

	cube.InitShader();
	cube.SetVertices(cubeVer);
	cube.SetColors(cubeCol);

	cube.position.x = 1;

	std::vector<glm::vec3> triVer, triCol;
	triVer.push_back(glm::vec3(-1.f, 1.f, 1.f));
	triVer.push_back(glm::vec3(-1.f, -1.f, 1.f));
	triVer.push_back(glm::vec3(1.f, -1.f, 1.f));

	triCol.push_back(glm::vec3(1.f, 0.f, 0.f));
	triCol.push_back(glm::vec3(0.f, 1.f, 0.f));
	triCol.push_back(glm::vec3(0.f, 0.f, 1.f));

	triangle.InitShader();
	triangle.SetVertices(triVer);
	triangle.SetColors(triCol);
	triangle.position.x = -1;
}

void Scene::update()
{
	mat4x4 model, view, proj;

	//glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//back face culling
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	//cube.rotation.x = glfwGetTime();
	//cube.rotation.z = glfwGetTime()/2;
	cube.Render(&camera);

	//triangle.rotation.z = glfwGetTime();
	triangle.Render(&camera);
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
