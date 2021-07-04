#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Utility.h"
#include "ShaderManager.h"
#include "Mesh.h"
#include "stb_image.h"

class Model {
private:
	string directory;
	vector<Mesh> meshes;

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, TextureType typeName);

public:
	Model() {

	}

	Model(char* path)
	{
		LoadModel(path);
	}

	void LoadModel(string path);

	void Draw(ShaderManger shader);
};