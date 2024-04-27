#pragma once
#include <Rayer/Core/Core.h>
#include <Rayer/RenderEngine/RendererApi.h>
#include <Rayer/RenderEngine/RenderEngine.h>
#include <Rayer/RenderEngine/RenderingPrimitives/Shader.h>
#include <Rayer/RenderEngine/RenderingPrimitives/Framebuffer.h>


namespace Rayer {

	class MeshBench : public RenderEngine{


		public:

			MeshBench();

			virtual void SetClearColor(const glm::vec4& color) override;
			virtual void Clear() override;

			virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) override;

		private:
			
			Ref<RendererApi> s_Api;

			//MeshBench related shader
			Scope<Shader> m_Shader;

		


	};

}