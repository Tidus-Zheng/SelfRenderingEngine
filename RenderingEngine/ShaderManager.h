#pragma once
#include "Utility.h"
#include <filesystem>

class ShaderManger {
	GLuint vertex_shader, fragment_shader, program;

	std::string ReadFromFile(const GLchar* pathToFile);
public:
	ShaderManger() { }

	~ShaderManger() {
		glDeleteProgram(program);
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
	}
	// shader file should in the fold named shader
	void init(std::string vertexShaderFileName, std::string fragmentShaderFileName);

	GLint GetUniformLocation(std::string name);
	GLint GetAttribLocation(std::string name);
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void UseProgram();
	GLint GetProgram() { return program; }
};
