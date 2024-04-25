#include <glad/glad.h>
#include <Rayer/Core/Application.h>
#include <Rayer/Core/Core.h>
#include <Platform/OpenGL/OpenGLRendererApi.h>


namespace Rayer {


	void OpenGLRendererApi::SetClearColor(const glm::vec4& color) {

		
		glClearColor(color.x, color.y, color.z, color.w);

	}

	void OpenGLRendererApi::Clear() {

		
		glClear(GL_COLOR_BUFFER_BIT);

	}

	void OpenGLRendererApi::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) {

		
		vertexArray->Bind();


		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);

	}
}