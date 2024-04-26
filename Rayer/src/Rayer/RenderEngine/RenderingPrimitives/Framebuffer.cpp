#include <Rayer/Core/Core.h>
#include <Rayer/Core/Assert.h>
#include <Rayer/Renderer/Renderer.h>
#include "Framebuffer.h"

#include <Platform/OpenGL/OpenGLFrameBuffer.h>

namespace Rayer {

	Ref<Framebuffer> Framebuffer::Create(const FrameBufferSpecification& spec) {

		switch(Renderer::GetApi()) {

			case RendererApi::Api::None: RAYER_CORE_ASSERT(false, "RendererApi::None is not supported .") return nullptr;
			case RendererApi::Api::OpenGL: return CreateRef<OpenGLFrameBuffer>(spec);

		}

	}

}