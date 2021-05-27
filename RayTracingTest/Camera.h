#pragma once
#include "Utility.h"

class Camera {
private:
	glm::vec3 position, lookAt, up;
	mat4x4 matrix;
	int width, height;
	float ratio;

public:
	Camera() {
		up = glm::vec3(0.f, 1.f, 0.f);
		position = glm::vec3(0.f, 0.f, 1.f);
		lookAt = glm::vec3(0.f, 0.f, 0.f);

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

	glm::vec3* GetPosition() { return &position; }
	void GetMVPMatrix(mat4x4& mvp);
	void UpdatePosition(glm::vec3 offset);
};