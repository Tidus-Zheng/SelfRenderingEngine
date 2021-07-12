#pragma once

#include "Utility.h"
#include "ShaderManager.h"
#include "Texture.h"

class Material {
private:

public:
	Texture diffuse, normal, specular;
	//ShaderManger* shader;
	unique_ptr<ShaderManger> shader;

	Material() {
		shader = make_unique<ShaderManger>();
		shader->init("vertex.vs", "fragment.fs");
	}

	~Material(){
		//delete shader;
	}

	void InitShader(string vsFileName, string fsFileName) {
		shader->init(vsFileName, fsFileName);
	}

	
};