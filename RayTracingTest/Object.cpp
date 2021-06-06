#include "Object.h"
#include <glm/gtc/type_ptr.hpp>

void Object::AttibuteValue(GLuint* buffer, GLint location, std::vector<glm::vec3> values)
{
	//GLuint buffer;
	glGenBuffers(1, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, *buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * values.size(), &values[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Object::AttributeVertices(ShaderManger* shader, std::string attribute)
{
	AttibuteValue(&vertexBuffer, shader->GetAttribLocation(attribute), vertices);
}

void Object::AttributeColors(ShaderManger* shader, std::string attribute)
{
	AttibuteValue(&colorBuffer, shader->GetAttribLocation(attribute), colors);
}

void Object::Render(Camera* camera)
{
	mat4x4 model, view, proj;

	GetModelMatrix(model);
	camera->GetViewMatrix(view);
	camera->GetProjMatrix(proj);

	simpleShader.UseProgram();
	AttributeVertices(&simpleShader, "vPos");
	AttributeColors(&simpleShader, "vCol"); 
	glUniformMatrix4fv(simpleShader.GetUniformLocation("model"), 1, GL_FALSE, (const GLfloat*)model);
	glUniformMatrix4fv(simpleShader.GetUniformLocation("view"), 1, GL_FALSE, (const GLfloat*)view);
	glUniformMatrix4fv(simpleShader.GetUniformLocation("proj"), 1, GL_FALSE, (const GLfloat*)proj);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

void Object::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

}


