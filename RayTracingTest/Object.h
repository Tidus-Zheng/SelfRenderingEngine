#pragma once
#include "Utility.h"
#include "ShaderManager.h"
#include "Camera.h"
#include <vector>

class Object {
private:
	GLint vao;
	GLuint vertexBuffer, colorBuffer;
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

	void SetVertices(std::vector<glm::vec3> _vertices) {
		vertices = _vertices;
	}

	void SetColors(std::vector < glm::vec3> _colors) {
		colors = _colors;
	}

	void GetModelMatrix(mat4x4 model) {
		mat4x4_identity(model);
		mat4x4_translate(model, position.x, position.y, position.z);
		mat4x4_scale_aniso(model, model, scale.x, scale.y, scale.z);

		//rotate
		mat4x4_rotate_X(model, model, rotation.x);
		mat4x4_rotate_Y(model, model, rotation.y);
		mat4x4_rotate_Z(model, model, rotation.z);
	}

	void AttibuteValue(GLuint* buffer, GLint location, std::vector<glm::vec3> values);
	void AttributeVertices(ShaderManger* shader, std::string attribute);
	void AttributeColors(ShaderManger* shader, std::string attribute);
	void InitShader() { simpleShader.init("vertex.vs", "fragment.fs"); }

	void Render(Camera* camera);

	~Object() {

	}
};