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
	glm::vec3 worldPos = camera->GetWoldPostionFromView(offset);
	glm::vec3 viewOrigin = camera->GetWoldPostionFromView(glm::vec3(0));

	glm::vec3 lookAt = camera->GetLookAt();
	auto newOffset = glm::normalize(viewOrigin - worldPos) *= 0.1;

	camera->SetLookAt(lookAt + newOffset);
	std::cout << glm::to_string(camera->GetLookAt()) << std::endl;
	glm::vec3 newPosition = lookAt + newOffset + armDir * armLength;
	camera->SetPosition(newPosition);
}

void CameraOrbitControl::Rotate(double offsetX, double offsetY)
{
	glm::vec3 lookAt = camera->GetLookAt();

	double sensitivity = 0.1;

	armDir = Vec3RotateX(armDir, glm::radians(offsetY));
	armDir = Vec3RotateY(armDir, glm::radians(offsetX));

	camera->SetPosition(lookAt + glm::normalize(armDir) * armLength);
}


