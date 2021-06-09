#include "Camera.h"

void Camera::GetMVPMatrix(mat4x4& mvp)
{
	mat4x4 v, p;
	GetViewMatrix(v);
	GetProjMatrix(p);
	//double width = 10.f;
	//mat4x4_ortho(p, -ratio, ratio, -width, width, width, -width);
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
	//std::cout << glm::to_string(lookDir) << std::endl;

	mat4x4_look_at(view, &position[0], &lookAt[0], &newUp[0]);
}

void Camera::GetProjMatrix(mat4x4& proj)
{
	mat4x4_perspective(proj, 0.53, ratio, near, far);
}

glm::vec3 Camera::GetWoldPostionFromView(glm::vec3 pos)
{
	mat4x4 proj, view, projInvers, viewInvers;
	GetProjMatrix(proj);
	GetViewMatrix(view);

	mat4x4_invert(projInvers, proj);
	mat4x4_invert(viewInvers, view);

	glm::vec4 v4Pos = glm::vec4(pos, 1);
	glm::vec4 result;
	mat4x4_mul_vec4(&result[0], projInvers, &v4Pos[0]);
	result /= result.w;
	mat4x4_mul_vec4(&v4Pos[0], viewInvers, &result[0]);

	return glm::vec3(v4Pos);
}
