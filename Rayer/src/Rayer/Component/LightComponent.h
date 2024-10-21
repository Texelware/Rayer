#pragma once

#include "Component.h"
#include <Rayer/Lights/DirectionalLight.h>
#include <Rayer/Lights/PointLight.h>
#include <Rayer/Lights/SpotLight.h>

namespace Rayer {

	class LightComponent : public Component {

	public:

		LightComponent(Light* light);

		virtual void OnUpdate() override;
		virtual void OnRender() override;

		LightType& GetLightType()  { return m_LightType; }
		Light* GetLight() { return m_Light; }

		void setLightColor(const glm::vec3& color , LightType lightType) {

			switch (lightType) {

			case LightType::Directional: {

				DirectionalLight* dirLight = dynamic_cast<DirectionalLight*>(m_Light);

				if (dirLight) {

					dirLight->SetColor(color);

				}

				break;
			}

			case LightType::Point: {

				PointLight* pointLight = dynamic_cast<PointLight*>(m_Light);

				if (pointLight) {

					pointLight->SetColor(color);

				}

				break;

			}

			case LightType::Spot : {

				SpotLight* spotLight = dynamic_cast<SpotLight*>(m_Light);

				if (spotLight) {

					spotLight->SetColor(color);

				}

				break;

			}


			}

		}

		void setLightIntensity(const float intensity, LightType lightType) {

			switch (lightType) {

			case LightType::Directional: {

				DirectionalLight* dirLight = dynamic_cast<DirectionalLight*>(m_Light);

				if (dirLight) {

					dirLight->SetIntensity(intensity);

				}

				break;
			}

			case LightType::Point: {

				PointLight* pointLight = dynamic_cast<PointLight*>(m_Light);

				if (pointLight) {

					pointLight->SetIntensity(intensity);

				}

				break;

			}

			case LightType::Spot : {

				SpotLight* spotLight = dynamic_cast<SpotLight*>(m_Light);

				if (spotLight) {

					spotLight->SetIntensity(intensity);

				}

				break;

			}

			}

		}

	private:


		Light* m_Light;
		LightType m_LightType;
		
		bool showColorPicker {false};

	};

}