#pragma once

#include <Rayer/Core/Core.h>
#include <Rayer/RenderEngine/RendererApi.h>


namespace Rayer {

	class OpenGLRendererApi : public RendererApi {

		public:
			
			virtual void SetClearColor(const glm::vec4& color) override;
			virtual void Clear() override;

			virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) override;
				

	};

}
