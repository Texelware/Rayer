
#include "Texture.h"
#include <Platform/OpenGL/OpenGLTexture.h>

#include <Rayer/Core/Assert.h>
#include <Rayer/Renderer/Renderer.h>

namespace Rayer {

	Ref<Texture2D> Texture2D::Create(const std::filesystem::path& _path) {

		switch (Renderer::GetApi()) {

			case RendererApi::Api::OpenGL: return CreateRef<OpenGLTexture2D>(_path); break;
			

		}

		RAYER_CORE_ASSERT(false, "Unknown RendererApi!");
		return nullptr;

	}


	Ref<Texture2D> Texture2D::Create(const std::string& _path) {

		switch (Renderer::GetApi()) {

		case RendererApi::Api::OpenGL: return CreateRef<OpenGLTexture2D>(_path); break;


		}

		RAYER_CORE_ASSERT(false, "Unknown RendererApi!");
		return nullptr;

	}

}