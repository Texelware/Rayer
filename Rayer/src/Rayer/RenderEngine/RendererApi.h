#pragma once

#include <Rayer/Core/Core.h>
#include <Rayer/RenderEngine/RenderingPrimitives/VertexArray.h>

#include <glm/glm.hpp>

namespace Rayer {


	class RendererApi {

	public:
		
		enum class Api {

			None = 0,
			OpenGL = 1,
			Vulkan = 2

		};

		virtual ~RendererApi() {}

		virtual void Init() = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		
		virtual void Clear() = 0;
		

		//Rendering related methods
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) = 0;
		virtual void DrawWireframe(const Ref<VertexArray>& vertexArray, uint32_t count) = 0;
		virtual void DrawLine(const Ref<VertexArray>& vertexArray, uint32_t count) = 0;

		static Api GetApi() { return s_Api; }

		static Ref<RendererApi> Create();

	private:
		
		static Api s_Api;

	};

}