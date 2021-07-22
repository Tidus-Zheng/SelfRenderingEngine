#include "Mesh.h"
#include "Scene.h"

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::uv));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::tangent));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::bitangent));

	glBindVertexArray(0);
}

Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices)
{
	this->vertices = vertices;
	this->indices = indices;
	this->material = make_unique<Material>();
	setupMesh();
}

//render with material
void Mesh::Draw(mat4x4 model) {
	mat4x4 m, view, proj;
	Camera* camera = Scene::Instance().camera;
	DirectionalLight* light = &Scene::Instance().directionLight;

	material->shader->UseProgram();
	camera->GetViewMatrix(view);
	camera->GetProjMatrix(proj);
	glUniformMatrix4fv(material->shader->GetUniformLocation("model"), 1, GL_FALSE, (const GLfloat*)model);
	glUniformMatrix4fv(material->shader->GetUniformLocation("view"), 1, GL_FALSE, (const GLfloat*)view);
	glUniformMatrix4fv(material->shader->GetUniformLocation("proj"), 1, GL_FALSE, (const GLfloat*)proj);

	glm::vec3 lightDir = light->GetDir();
	glm::vec3 lightColor = light->color;
	glm::vec3 cameraPosition = camera->GetPosition();
	glUniform3f(material->shader->GetUniformLocation("lightDir"), lightDir.x, lightDir.y, lightDir.z);
	glUniform3f(material->shader->GetUniformLocation("lightColor"), lightColor.x, lightColor.y, lightColor.z);
	glUniform3f(material->shader->GetUniformLocation("cameraPos"), cameraPosition.x, cameraPosition.y, cameraPosition.z);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, material->diffuse.GetID());

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, material->normal.GetID());

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, material->specular.GetID());

	//glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
