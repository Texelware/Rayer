#pragma once

#include <Rayer/Core/Core.h>
#include <Rayer/RenderEngine/RendererApi.h>


namespace Rayer {

	class OpenGLRendererApi : public RendererApi {

		public:
			
			void Init() override;
			virtual void SetClearColor(const glm::vec4& color) override;
			virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
			virtual void Clear() override;

			virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) override;
			virtual void DrawWireframe(const Ref<VertexArray>& vertexArray, uint32_t count) override;
			virtual void DrawLine(const Ref<VertexArray>& vertexArray, uint32_t count) override;
				

	};

}
