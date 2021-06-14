#pragma once
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#undef GLFW_INCLUDE_NONE
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <glm/glm.hpp>
#include <linmath.h>
#include "glm/gtx/string_cast.hpp"
#include "glm/gtc/constants.hpp"

using namespace std;

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
	glm::vec3 tangent;
	glm::vec3 bitangent;
};

enum TextureType {
	diffuse = 'd',
	specular = 's'
};

//struct Texture {
//	unsigned int id;
//	TextureType type;
//};