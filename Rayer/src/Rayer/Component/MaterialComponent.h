#pragma once

#include <Rayer/RenderEngine/RenderingPrimitives/Texture.h>
#include "Component.h"
#include <Rayer/Utils/PlatformUtils.h>

#include <Rayer/Material/PBR_Material.h>
#include <Rayer/Material/BASIC_Material.h>

namespace Rayer {

	
	class MaterialComponent : public Component {

	public:

		MaterialComponent();
		MaterialComponent(Ref<Material> material);
		

		virtual void OnRender() override;
		virtual void OnUpdate() override;

		Ref<Material>& GetMaterial() { return m_material; }

	private:

		Ref<Texture2D> checkerboard_texture;


		Scope<PlatformUtils> m_platformUtils;

		Ref<Material> m_material;


		std::vector<std::string> items {"PBR", "BASIC"};
		int currentItem;
		std::string comboPreviewValue = items[0];

		bool showColorPicker = false;

	};

}