#include "Spheremap.h"
#include <Platform/OpenGL/OpenGLSpheremap.h>
#include <Rayer/Renderer/Renderer.h>

namespace Rayer {

	Ref<Spheremap> Spheremap::Create(const std::filesystem::path& _path) {

		switch (Renderer::GetApi()) {

		case RendererApi::Api::None: RAYER_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr; break;
		case RendererApi::Api::OpenGL: return CreateRef<OpenGLSpheremap>(_path);  break;
		}

	}

}