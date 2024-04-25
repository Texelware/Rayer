#pragma once
#include <Rayer/Core/Core.h>
#include <Rayer/RenderEngine/RenderEngine.h>
#include <Rayer/RenderEngine/MeshBench/MeshBench.h>

#include <Rayer/RenderEngine/RenderingPrimitives/VertexArray.h>


#include <glm/glm.hpp>


namespace Rayer {

	class RenderCommand {

		public:

			static void SetClearColor(const glm::vec4& color) {

				MESH_BENCH_ENGINE->SetClearColor(color);

			}

			static void Clear() {

				MESH_BENCH_ENGINE->Clear();

			}

			static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) {

				MESH_BENCH_ENGINE->DrawIndexed(vertexArray, count);

			}

			
		private:

			static Scope<MeshBench> MESH_BENCH_ENGINE;

	};

}