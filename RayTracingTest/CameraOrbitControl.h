#pragma once

#include "Camera.h"
#include "glm/gtx/projection.hpp"

class CameraOrbitControl {
private:
	Camera* camera;
	float armLength = 1;
	glm::vec3 armDir = glm::vec3(0, 0, 1);
	glm::vec3 baseVector = glm::vec3(1, 0, 0);

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
	void ArmLengthUpdate(double offset);
	void UpdateCameraPosition();

	glm::vec3 Vec3RotateX(glm::vec3 vector, double angle) {
		glm::mat3x3 rotMat(1, 0, 0, 0, cos(angle), -sin(angle), 0, sin(angle), cos(angle));
		return rotMat * vector;
	}

	glm::vec3 Vec3RotateY(glm::vec3 vector, double angle) {
		glm::mat3x3 rotMat(cos(angle), 0, sin(angle), 0, 1, 0, -sin(angle), 0, cos(angle));
		return rotMat * vector;
	}

	glm::vec3 Vec3RotateZ(glm::vec3 vector, double angle) {
		glm::mat3x3 rotMat(cos(angle), -sin(angle), 0, sin(angle), cos(angle), 0, 0, 0, 1);
		return rotMat * vector;
	}
};