#include "CameraOrbitControl.h"
#define Log(vec3) std::cout<<glm::to_string(vec3)<<std::endl;

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
	UpdateCameraPosition();
}

void CameraOrbitControl::Rotate(double offsetX, double offsetY)
{
	double sensitivity = 0.01;

	glm::vec3 projDir = glm::normalize(glm::vec3(armDir.x, 0, armDir.z));

	float xAngle = acos(glm::dot(baseVector, projDir));
	float yAngle = acos(glm::dot(armDir, projDir));

	if (projDir.z < 0)
		xAngle = glm::two_pi<float>() - xAngle;

	if (armDir.y < 0)
		yAngle = -yAngle;

	xAngle += offsetX * sensitivity;
	yAngle += offsetY * sensitivity;

	yAngle = std::min(glm::half_pi<float>() * 0.99f, yAngle);
	yAngle = std::max(-glm::half_pi<float>() * 0.99f, yAngle);

	glm::vec3 newDir(baseVector);
	newDir = Vec3RotateZ(newDir, -yAngle);
	newDir = Vec3RotateY(newDir, xAngle);

	armDir = glm::normalize(newDir);
	UpdateCameraPosition();
}

void CameraOrbitControl::ArmLengthUpdate(double offset)
{
	glm::vec3 lookAt = camera->GetLookAt();

	double sensitivity = 1.f;
	armLength += offset * sensitivity;

	camera->SetPosition(lookAt + glm::normalize(armDir) * armLength);
}

void CameraOrbitControl::UpdateCameraPosition()
{
	camera->SetPosition(camera->GetLookAt() + armDir * armLength);
}






