#pragma once

#include "Light.h"
#include <glm/glm.hpp>

namespace Rayer {

    struct SpotLightProps {

        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 color;
        float intensity;

        float cutOff;

        float constant;
        float linear;
        float quadratic;
    };


    class SpotLight : public Light {

    public:

        SpotLight(const std::string& name);

        SpotLightProps& GetLightProperties() { return lightProps; }

        void CalculatePosition();

		void CalculateDirection();

    private:

        glm::mat4 modelMatrix{ 1 };

        SpotLightProps lightProps{

            // Main properties of the light
            {1.0f , 1.0f, 1.0f},  // position
            {0.0f, -1.0f, 0.0f},  // direction
            {1.0f , 1.0f , 1.0f}, // color
            1.0f,                 // intensity

            // Cutoff angle
            glm::cos(glm::radians(20.0f)),  // cutOff

            // Attenuation factors
            1.0f,   // constant
            0.09f,  // linear
            0.032f  // quadratic
        };

    };

}
