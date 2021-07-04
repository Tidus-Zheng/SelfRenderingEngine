#pragma once

#include "Utility.h"
#include "ShaderManager.h"
#include "Texture.h"
#include "Material.h"
//#include "Scene.h"

class Mesh {
private:
	GLuint VAO, VBO, EBO;
	void setupMesh();

public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	Material material;
	vector<Texture> textures;

	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, Material material);

	void Draw(ShaderManger shader);
	//render with material
	void Draw();
};
