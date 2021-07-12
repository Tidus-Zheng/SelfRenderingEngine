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
	vector<Texture> textures;
	unique_ptr<Material> material;

	Mesh(vector<Vertex> vertices, vector<GLuint> indices);

	//render with material
	void Draw(mat4x4 model);
};
