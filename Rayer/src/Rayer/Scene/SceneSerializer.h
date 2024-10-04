#pragma once



#include "rpch.h"
#include <filesystem>

namespace Rayer {
	
	class Scene;

	class SceneSerializer {

	public:

		SceneSerializer(Scene* scene);
		SceneSerializer() = delete;
		

		void Serialize(const std::filesystem::path& filepath); 
		void Deserialize(const std::filesystem::path& filepath);

	private:

		Scene* mScene = nullptr;

	};


}