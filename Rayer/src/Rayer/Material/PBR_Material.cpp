#include "PBR_Material.h"


namespace Rayer {

	PBR_Material::PBR_Material() : Material(MaterialType::PBR) {

		m_Maps = CreateRef<MaterialMaps>();

	}

	void PBR_Material::Reset() {

		//Reseting the material
		m_Maps->albedo = nullptr;
		m_Maps->normal = nullptr;

		//Reseting the material maps status
		m_textureAvailabilityStatus.has_albedo = false;
		m_textureAvailabilityStatus.has_normal = false;

	}

	void PBR_Material::Update(Ref<Texture2D>& _map, const MapType _type , std::filesystem::path filepath) {

		switch (_type) {

			case MapType::Albedo :

				m_Maps->albedo = std::move(_map);
				m_textureAvailabilityStatus.has_albedo = true;
				m_texturePaths.albedo_path = std::move(filepath);


				break;

			case MapType::Normal :

				m_Maps->normal = std::move(_map);
				m_textureAvailabilityStatus.has_normal = true;
				m_texturePaths.normal_path = std::move(filepath);

				break;
		}

		//Updating the texture availability status based on the available texture maps
		if (!m_textureAvailabilityStatus.has_albedo && !m_textureAvailabilityStatus.has_normal) {
			m_availableTextureMaps = NoTextureMaps;
		}
		else if (m_textureAvailabilityStatus.has_albedo && !m_textureAvailabilityStatus.has_normal) {
			m_availableTextureMaps = Albedo;
		}
		else if (!m_textureAvailabilityStatus.has_albedo && m_textureAvailabilityStatus.has_normal) {
			m_availableTextureMaps = Normal;
		}
		else if (m_textureAvailabilityStatus.has_albedo && m_textureAvailabilityStatus.has_normal) {
			m_availableTextureMaps = (Albedo | Normal);
		}

	}



}