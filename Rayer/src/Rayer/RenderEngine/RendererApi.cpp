#include <Rayer/RenderEngine/RendererApi.h>
#include <Rayer/Core/Assert.h>

#include <Platform/OpenGL/OpenGLRendererApi.h>

namespace Rayer {

	RendererApi::Api RendererApi::s_Api = RendererApi::Api::OpenGL;

	Ref<RendererApi> RendererApi::Create() {

		switch (RendererApi::GetApi()) {

			case RendererApi::Api::None: RAYER_CORE_ASSERT(false, "RendererApi::None is not supported .") return nullptr;
			case RendererApi::Api::OpenGL: return CreateRef<OpenGLRendererApi>();

		}

	}

}