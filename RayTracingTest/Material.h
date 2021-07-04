#pragma once

#include "Utility.h"
#include "ShaderManager.h"
#include "Texture.h"

class Material {
private:

public:
	Texture diffuse, normal, specular;
	ShaderManger shader;

	Material() {
		shader.init("vertex.vs", "phongFragment.fs");
	}

	~Material(){

	}

	void InitShader(string vsFileName, string fsFileName) {
		shader.init(vsFileName, fsFileName);
	}

	
};