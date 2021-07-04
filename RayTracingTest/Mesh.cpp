#include "Mesh.h"

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
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

	glBindVertexArray(0);
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}

Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices, Material material)
{
	this->vertices = vertices;
	this->indices = indices;
	this->material = material;

	setupMesh();
}

void Mesh::Draw(ShaderManger shader)
{
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	for (GLuint i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		//string number;
		//if (textures[i].type == diffuse)
		//	number = std::to_string(diffuseNr++);
		//else if (textures[i].type == specular)
		//	number = std::to_string(specularNr++);

		//shader.setFloat(("material." + textures[i].type + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].GetID());
	}
	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

//render with material
void Mesh::Draw() {
	mat4x4 m, view, proj;
	material.shader.UseProgram();

	glActiveTexture(GL_TEXTURE0);
	//material.shader.setFloat("texture_d1", 0);
	glBindTexture(GL_TEXTURE_2D, material.diffuse.GetID());

	glActiveTexture(GL_TEXTURE1);
	//material.shader.setFloat("texture_d2", 0);
	glBindTexture(GL_TEXTURE_2D, material.normal.GetID());

	glActiveTexture(GL_TEXTURE2);
	//material.shader.setFloat("texture_d2", 0);
	glBindTexture(GL_TEXTURE_2D, material.specular.GetID());

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//Scene::camera;

	//mat4x4_identity(m);
	//scene.camera.GetViewMatrix(view);
	//scene.camera.GetProjMatrix(proj);
	//glUniformMatrix4fv(material.shader.GetUniformLocation("model"), 1, GL_FALSE, (const GLfloat*)m);
	//glUniformMatrix4fv(material.shader.GetUniformLocation("view"), 1, GL_FALSE, (const GLfloat*)view);
	//glUniformMatrix4fv(material.shader.GetUniformLocation("proj"), 1, GL_FALSE, (const GLfloat*)proj);
	
}
