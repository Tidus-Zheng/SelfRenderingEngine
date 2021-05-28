#include "Object.h"
#include <glm/gtc/type_ptr.hpp>

void Object::AttibuteValue(GLint location, std::vector<glm::vec3> values)
{
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * values.size(), &values[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
}

void Object::AttributeVertices(ShaderManger* shader, std::string attribute)
{
	AttibuteValue(shader->GetAttribLocation(attribute), vertices);
}

void Object::AttributeColors(ShaderManger* shader, std::string attribute)
{
	AttibuteValue(shader->GetAttribLocation(attribute), colors);
}

void Object::Render()
{
	GLint mvp_location, vpos_location, vcol_location;

	mvp_location = simpleShader.GetUniformLocation("MVP");

	AttributeVertices(&simpleShader, "vPos");
	AttributeColors(&simpleShader, "vCol");

	//mat4x4_identity(matrix);
	//mat4x4_rotate_Z(matrix, matrix, (float)glfwGetTime());

	//camera.GetMVPMatrix(mvp);
	//mat4x4_mul(mvp, mvp, m);

}
