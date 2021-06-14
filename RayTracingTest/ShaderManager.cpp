#include "ShaderManager.h"

#define shader_path "E:/ray tracing/ray-tracing/RayTracingTest/shader/"

std::string ShaderManger::ReadFromFile(const GLchar* pathToFile)
{
	std::string content;
	std::ifstream fileStream(pathToFile, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << pathToFile << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	//std::cout << "'" << content << "'" << std::endl;
	return content;
}

void ShaderManger::init(std::string vertexShaderFileName, std::string fragmentShaderFileName) {
	std::string vertexShaderSrc = ReadFromFile((shader_path + vertexShaderFileName).c_str());
	std::string fragmentShaderSrc = ReadFromFile((shader_path + fragmentShaderFileName).c_str());

	const char* vertexPointer = vertexShaderSrc.c_str();
	const char* fragmentPointer = fragmentShaderSrc.c_str();

	program = glCreateProgram();

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertexPointer, NULL);
	glCompileShader(vertex_shader);

	GLint result;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		GLint length;
		glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(vertex_shader, length, &length, &error[0]);
		std::cout << "Failed to compile vertex shader: " << &error[0] << std::endl;
		glDeleteShader(vertex_shader);
	}

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragmentPointer, NULL);
	glCompileShader(fragment_shader);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		GLint length;
		glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(fragment_shader, length, &length, &error[0]);
		std::cout << "Failed to compile fragment shader: " << &error[0] << std::endl;
		glDeleteShader(fragment_shader);
	}
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
}

GLint ShaderManger::GetUniformLocation(std::string name) {
	return glGetUniformLocation(program, name.c_str());
}

GLint ShaderManger::GetAttribLocation(std::string name)
{
	return glGetAttribLocation(program, name.c_str());
}

void ShaderManger::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
}

void ShaderManger::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}

void ShaderManger::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

void ShaderManger::UseProgram()
{
	glUseProgram(program);
}
