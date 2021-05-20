#include "Object.h"
#include <glm/gtc/type_ptr.hpp>

void Object::AttributeVertices(GLint location)
{
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 12, (void*)0);
}

void Object::AttributeColors(GLint location)
{
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), &colors[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 12, (void*)0);
}
