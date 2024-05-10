#pragma once
#include <Rayer/Core/Core.h>
#include <Rayer/RenderEngine/RendererApi.h>
#include <Rayer/RenderEngine/RenderingPrimitives/VertexArray.h>

#include <glm/glm.hpp>

namespace Rayer {


	//Interface for Render Engine => Must be implemented by any concrete Render Engines
	class RenderEngine {


	public:

		virtual void Init() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) = 0;
		virtual void DrawWireframe(const Ref<VertexArray>& vertexArray, uint32_t count) = 0;
		virtual void DrawLine(const Ref<VertexArray>& vertexArray, uint32_t count) = 0;

		static Ref<RendererApi> GetActiveApi() { return s_RendererApi; }

	public:

		static Ref<RendererApi> s_RendererApi;

	};

}