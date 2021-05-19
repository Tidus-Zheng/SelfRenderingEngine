#pragma once
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class ShaderManger {
	GLuint vertex_shader, fragment_shader;

public:
	void init(std::string vertexShaderFileName, std::string fragmentShaderFileName);
	std::string readFromFile(const GLchar* pathToFile);

	GLuint GetFragmentShader() { return fragment_shader; }
	GLuint GetVertexShader() { return vertex_shader; }
};
