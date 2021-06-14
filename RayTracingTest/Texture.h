#pragma once

#include "Utility.h"
#include "stb_image.h"

class Texture {
private:
	GLuint id;
	int width, height, channels;
public:
	TextureType type;

	Texture(string path);

	GLuint GetID() { return id; }
};