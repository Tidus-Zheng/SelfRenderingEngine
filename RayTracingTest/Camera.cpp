#include "Camera.h"

void Camera::GetMVPMatrix(mat4x4& mvp)
{
	mat4x4 v, p;
	mat4x4_look_at(v, &position[0], &lookAt[0], &up[0]);
	mat4x4_perspective(p, height, ratio, 0.1, 1000);
	//mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	mat4x4_mul(mvp, p, v);
}

void Camera::UpdatePosition(glm::vec3 offset)
{
	position += offset;
}
