#pragma once
#include "Utility.h"
#include "glm/gtx/rotate_vector.hpp"

class Camera {
private:
	glm::vec3 position, lookAt, up;
	mat4x4 matrix;
	int width, height;
	float near, far;
	float ratio;

public:
	Camera() {
		up = glm::vec3(0.f, 1.f, 0.f);
		position = glm::vec3(10.f, 10.f, 10.f);
		lookAt = glm::vec3(0.f, 0.f, 0.f);

		near = 0.1f;
		far = 1000.f;

		mat4x4_identity(matrix);
	}

	Camera(int _width, int _height) : Camera()
	{
		SetResulution(_width, _height);
	}


	void SetResulution(int _width, int _height)
	{
		width = _width;
		height = _height;
		ratio = width / (float)height;
	}

	glm::vec3 GetPosition() { return position; }
	void SetPosition(glm::vec3 _position) { position = _position; }
	
	glm::vec3 GetLookAt() { return lookAt; }
	void SetLookAt(glm::vec3 _lookAt) { lookAt = _lookAt; }

	void GetMVPMatrix(mat4x4& mvp);
	void GetViewMatrix(mat4x4& view);
	void GetProjMatrix(mat4x4& proj);
	void UpdatePosition(glm::vec3 offset);
};