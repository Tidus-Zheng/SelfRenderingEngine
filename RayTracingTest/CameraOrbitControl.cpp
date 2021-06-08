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
	std::cout << glm::to_string(camera->GetLookAt()) << std::endl;
	glm::vec3 newPosition = lookAt + newOffset + armDir * armLength;
	camera->SetPosition(newPosition);
}

void CameraOrbitControl::Rotate(double offsetX, double offsetY)
{
	glm::vec3 lookAt = camera->GetLookAt();

	double sensitivity = 0.1;
	glm::vec3 projDir = glm::normalize(glm::vec3(armDir.x, 0, armDir.z));// glm::normalize(glm::proj(armDir, glm::vec3(1, 0, 1)));

	float xAngle = acos(glm::dot(glm::vec3(1, 0, 0), projDir));
	float yAngle = acos(glm::dot(armDir, projDir));

	if (projDir.z < 0)
		xAngle = -xAngle;

	if (armDir.y < 0)
		yAngle = -yAngle;

	//yAngle = std::min((double)1.57f, yAngle + offsetY * 0.01);
	//yAngle = std::max((double)-1.57f, yAngle + offsetY * 0.01);

	std::cout << glm::degrees(yAngle) << std::endl;
	glm::vec3 newDir(1, 0, 1);
	//newDir = Vec3RotateY(newDir, xAngle);
	newDir = Vec3RotateX(newDir, yAngle);
	//Log(glm::normalize(newDir));
	armDir = glm::normalize(newDir);
	camera->SetPosition(lookAt + glm::normalize(armDir) * armLength);
}

void CameraOrbitControl::ArmLengthUpdate(double offset)
{
	glm::vec3 lookAt = camera->GetLookAt();

	double sensitivity = 0.1;
	armLength += offset * sensitivity;

	camera->SetPosition(lookAt + glm::normalize(armDir) * armLength);
}

void CameraOrbitControl::UpdateCameraPosition(glm::vec3 position)
{

}






