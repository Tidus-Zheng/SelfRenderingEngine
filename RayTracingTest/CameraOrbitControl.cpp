#include "CameraOrbitControl.h"

void CameraOrbitControl::SetCamera(Camera* _camera)
{
	camera = _camera;
	glm::vec3 lookAtDir = camera->GetPosition() - camera->GetLookAt();
	armDir = glm::normalize(lookAtDir);
	armLength = glm::length(lookAtDir);
}

void CameraOrbitControl::Move(glm::vec3 offset)
{
	glm::vec3 lookAt = camera->GetLookAt();
	camera->SetLookAt(lookAt + offset);
	glm::vec3 newPosition = lookAt + offset + armDir * armLength;
	std::cout << glm::to_string(newPosition) << std::endl;
	camera->SetPosition(newPosition);
}

void CameraOrbitControl::Rotate(double offsetX, double offsetY)
{
	glm::vec3 lookAt = camera->GetLookAt();

	double sensitivity = 0.001;
	//armDir = glm::rotateX(armDir, offsetX);
	armDir.x += offsetX * sensitivity;
	armDir.y -= offsetY * sensitivity;

	camera->SetPosition(lookAt + glm::normalize(armDir) * armLength);
}


