#pragma once
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class ShaderManger {
	GLuint vertex_shader, fragment_shader, program;

	std::string ReadFromFile(const GLchar* pathToFile);
public:
	ShaderManger() {

	}

	~ShaderManger() {
		glDeleteProgram(program);
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
	}
	// shader file should in the fold named shader
	void init(std::string vertexShaderFileName, std::string fragmentShaderFileName);

	GLint GetUniformLocation(std::string name);
	GLint GetAttribLocation(std::string name);
	void UseProgram();
};
