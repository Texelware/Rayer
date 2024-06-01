#pragma once
#include "Light.h"
#include <glm/glm.hpp>

namespace Rayer {

	class SkyLight : public Light {


	public:

		SkyLight(std::string name);

	private:

		glm::mat4 modelMatrix{ glm::mat4(1) };

	};

}