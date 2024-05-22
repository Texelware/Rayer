#pragma once

#include <Rayer/RenderEngine/RenderingPrimitives/Texture.h>
#include <filesystem>
#include <Rayer/Utils/PlatformUtils.h>


namespace Rayer {
	
	namespace fs = std::filesystem;

	class ContentBrowserPanel {

		public:

			ContentBrowserPanel();

			void OnImGuiRender();

			void OnFileDropped(int count, const char** paths);

		private:

			std::string assetDir;

			Ref<Texture2D> directoryTexture;
			Ref<Texture2D> fileTexture;
			Ref<Texture2D> backTexture;
			Ref<Texture2D> importTexture;
			Ref<Texture2D> modelTexture;

			static bool showContentBrowser;
			
			Scope<PlatformUtils> m_PlatformUtils;

			fs::path m_CurrentDirectory;
			fs::path m_BaseDirectory;
	};

}