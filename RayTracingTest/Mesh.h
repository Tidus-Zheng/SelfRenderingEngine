#pragma once

#include "Utility.h"
#include "ShaderManager.h"
#include "Texture.h"

class Mesh {
private:
	GLuint VAO, VBO, EBO;
	void setupMesh();

public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
	//Init(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(ShaderManger shader);
};
