#include "DirectionalLight.h"

glm::vec3 DirectionalLight::GetDir()
{
	return lookAt - position;
}
