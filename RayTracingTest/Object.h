#pragma once
#include "Utility.h"
#include "ShaderManager.h"
#include <vector>

class Object {
private:
public:
	std::vector<glm::vec3> vertices, colors, triangles, normal;
	std::vector<glm::vec2> uvs;
	glm::vec3 position, rotation, scale;
	mat4x4 matrix;

	ShaderManger simpleShader;

	Object() {
		scale = glm::vec3(1, 1, 1);
	}

	Object(std::vector<glm::vec3> _vertices) :Object() {
		vertices = _vertices;

		for (int i = 0; i < vertices.size(); i++) {
			colors.push_back(glm::vec3(1, 1, 1));
		}
	}

	Object(std::vector<glm::vec3> _vertices, std::vector<glm::vec3> _colors) :Object() {
		vertices = _vertices;
		colors = _colors;
	}

	void AttibuteValue(GLint location, std::vector<glm::vec3> values);
	void AttributeVertices(GLint location);
	void AttributeColors(GLint location);

	void Render();

	~Object() {

	}
};