#pragma once

#include "Utility.h"
#include "stb_image.h"
//#include <filesystem>
#include <assimp/scene.h>

class Texture {
private:
	int width, height, channels;
	GLuint id;

	void MakeTextureByPath(string path);
public:
	TextureType type;
	aiString path;

	Texture() {

	}

	Texture(string path) { MakeTextureByPath(path); }

	void TextureFromFile(const char* path, const string& directory, bool gamma = false);

	GLuint GetID() { return id; }
};