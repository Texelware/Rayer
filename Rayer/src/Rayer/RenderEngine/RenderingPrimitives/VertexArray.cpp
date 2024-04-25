#include <Rayer/Core/Core.h>
#include <Rayer/Core/Assert.h>
#include <Rayer/Renderer/Renderer.h>
#include <Rayer/RenderEngine/RenderingPrimitives/VertexArray.h>
#include <Platform/OpenGL/OpenGLVertexArray.h>

namespace Rayer {

	Ref<VertexArray> VertexArray::Create() {

		switch (Renderer::GetApi()) {

			case RendererApi::Api::None: RAYER_CORE_ASSERT(false, "RendererApi::None is not supported .") return nullptr;
			case RendererApi::Api::OpenGL: return CreateRef<OpenGLVertexArray>();

		}

	}

}