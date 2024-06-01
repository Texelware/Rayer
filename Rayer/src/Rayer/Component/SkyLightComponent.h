#pragma once

#include "Component.h"
#include <Rayer/Spheremap/Spheremap.h>
#include <Rayer/Filesystem/FileSystem.h>
#include <Rayer/RenderEngine/RenderingPrimitives/Texture.h>
#include <Rayer/Utils/PlatformUtils.h>

namespace Rayer {


	class SkyLightComponent : public Component {

	public:

		SkyLightComponent();
		virtual void OnUpdate() override;
		virtual void OnRender() override;

		void Activate();

	private:

		
		fs::path _hdrPath;

		Ref<Spheremap> spheremap;

		Ref<Texture2D> folderIcon;

		Ref<PlatformUtils> platformUtils;
	};

}