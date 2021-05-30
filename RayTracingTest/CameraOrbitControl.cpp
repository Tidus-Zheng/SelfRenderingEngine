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
	camera->SetPosition(newPosition);
}
