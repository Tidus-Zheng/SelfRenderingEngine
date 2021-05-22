#include "Object.h"
#include <glm/gtc/type_ptr.hpp>

void Object::AttibuteValue(GLint location, std::vector<glm::vec3> values)
{
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*values.size(), &values[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3) , (void*)0);
}

void Object::AttributeVertices(GLint location)
{
	AttibuteValue(location, vertices);
}

void Object::AttributeColors(GLint location)
{
	AttibuteValue(location, colors);
}
