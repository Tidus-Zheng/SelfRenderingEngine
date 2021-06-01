#pragma once

#include "Camera.h"

class CameraOrbitControl {
private:
	Camera* camera;
	float armLength = 1;
	glm::vec3 armDir = glm::vec3(0, 0, 1);

public:
	CameraOrbitControl() {

	}

	CameraOrbitControl(Camera* _camera) : camera(_camera) {
		glm::vec3 lookAtDir = camera->GetPosition() - camera->GetLookAt();
		armDir = glm::normalize(lookAtDir);
		armLength = glm::length(lookAtDir);
	}

	~CameraOrbitControl() {

	}

	void SetCamera(Camera* _camera);
	void Move(glm::vec3 offset);
	void Rotate(double offsetX, double offsetY);
};