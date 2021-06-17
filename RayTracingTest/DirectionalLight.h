#pragma once

#include "Utility.h"

class DirectionalLight {
private:

public:
	glm::vec3 position = glm::vec3(0.5, 0.5, 0.5);
	glm::vec3 lookAt = glm::vec3(0, 0, 0);
	glm::vec3 color = glm::vec3(1, 1, 1);

	DirectionalLight() {

	}

	~DirectionalLight(){

	}

	glm::vec3 GetDir();

};