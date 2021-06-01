#include "Camera.h"

void Camera::GetMVPMatrix(mat4x4& mvp)
{
	mat4x4 v, p;
	mat4x4_look_at(v, &position[0], &lookAt[0], &up[0]);
	mat4x4_perspective(p, height, ratio, near, far);
	//mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	mat4x4_mul(mvp, p, v);
}

void Camera::UpdatePosition(glm::vec3 offset)
{
	position += offset;
}

void Camera::GetViewMatrix(mat4x4& view)
{
	glm::vec3 lookDir = glm::normalize(position - lookAt);
	glm::vec3 right = glm::normalize(glm::cross(up, lookDir));
	glm::vec3 newUp = glm::normalize(glm::cross(lookDir, right));
	std::cout << glm::to_string(position) << std::endl;

	mat4x4_look_at(view, &position[0], &lookAt[0], &newUp[0]);
}

void Camera::GetProjMatrix(mat4x4& proj)
{
	mat4x4_perspective(proj, 0.53, ratio, near, far);
}
