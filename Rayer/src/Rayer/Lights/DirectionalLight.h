#pragma once

#include "Light.h"
#include <glm/glm.hpp>

namespace Rayer {

	struct DirectionalLightProps {

		glm::vec3 direction;
		glm::vec3 color;
		float intensity;

	};

	class DirectionalLight : public Light {


	public:

		DirectionalLight(const std::string& name);

		void CalculateDirection();

		DirectionalLightProps& GetLightProperties() { return lightProps; }

		// Method to get the light's projection matrix for shadow mapping
		glm::mat4 GetProjectionMatrix(float left, float right, float bottom, float top, float nearPlane, float farPlane) const;


		

	private:

		glm::mat4 modelMatrix { 1 };

		DirectionalLightProps lightProps {

			{ 0.0f, -1.0f, 0.0f } ,
			{1.0f, 1.0f, 1.0f }   ,
			1.0f
 
		};

	};

}