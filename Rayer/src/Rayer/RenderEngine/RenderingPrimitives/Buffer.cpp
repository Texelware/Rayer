#include <Rayer/Core/Core.h>
#include <Rayer/Core/Assert.h>
#include <Rayer/Renderer/Renderer.h>
#include <Rayer/RenderEngine/RenderingPrimitives/Buffer.h>
#include <Platform/OpenGL/OpenGLBuffer.h>

namespace Rayer {

	//Vertex buffer universal factory
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {

		switch (Renderer::GetApi()) {

			case RendererApi::Api::None: RAYER_CORE_ASSERT(false, "RendererApi::None is not supported .") return nullptr;

			case RendererApi::Api::OpenGL: return CreateRef<OpenGLVertexBuffer>(vertices,size);


		}

	}

	//Index buffer universal factory
	Ref<IndexBuffer> IndexBuffer::Create(unsigned int *indices, uint32_t count) {

		switch (Renderer::GetApi()) {

			case RendererApi::Api::None: RAYER_CORE_ASSERT(false, "RendererApi::None is not supported .") return nullptr;
			case RendererApi::Api::OpenGL: return CreateRef<OpenGLIndexBuffer>(indices , count);

		}

	}


	



}