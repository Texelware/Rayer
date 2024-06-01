#pragma once

#include "Light.h"
#include <glm/glm.hpp>

namespace Rayer {

    struct PointLightProps {

        glm::vec3 position;
        glm::vec3 color;
        float intensity;

        float constant;
        float linear;
        float quadratic;
    };


	class PointLight : public Light {

    public:

        PointLight(const std::string& name);

        PointLightProps& GetLightProperties() { return lightProps; }

        void CalculatePosition();

    private:

        glm::mat4 modelMatrix{ 1 };

        PointLightProps lightProps{
            
			//Main properties of the light
            {1.0f , 1.0f, 1.0f},
            {1.0f , 1.0f , 1.0f},
            1.0f,

			//Those are only for point light calculations
            1.0f,
            0.09f,
            0.032f

        };

	};

}