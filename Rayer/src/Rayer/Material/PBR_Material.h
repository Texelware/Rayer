#pragma once

#include "Material.h"
#include <Rayer/RenderEngine/RenderingPrimitives/Texture.h>

namespace Rayer {

	struct TextureAvailabilityStatus {

		bool has_albedo{ false };
		bool has_normal{ false };

	};

	enum class MapType {

		None = 0,
		Albedo = 1,
		Normal = 2,

	};

	enum AvailableTextureMaps : uint32_t {

		NoTextureMaps = 0,
		Albedo = 1,
		Normal = 2

	};

	struct MaterialMaps {

		Ref<Texture2D> albedo { nullptr };
		Ref<Texture2D> normal { nullptr };

	};

	class PBR_Material : public Material {

	public:

		PBR_Material();

		virtual void Reset() override;

		void Update(Ref<Texture2D>& _map, const MapType _type);

		Ref<MaterialMaps>& GetMaterialMaps() { return m_Maps; }
		TextureAvailabilityStatus& GetTextureAvailabilityStatus() { return m_textureAvailabilityStatus; }

		uint32_t GetAvailableTextureMaps() { return m_availableTextureMaps; }

	private:

		Ref<MaterialMaps> m_Maps;

		TextureAvailabilityStatus m_textureAvailabilityStatus;

		uint32_t m_availableTextureMaps{ NoTextureMaps };
	};

}