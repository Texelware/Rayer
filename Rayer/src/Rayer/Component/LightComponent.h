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


	private:


		Light* m_Light;
		LightType m_LightType;
		
		bool showColorPicker {false};

	};

}