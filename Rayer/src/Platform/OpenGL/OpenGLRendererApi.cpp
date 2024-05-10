#include <glad/glad.h>
#include <Rayer/Core/Application.h>
#include <Rayer/Core/Core.h>
#include <Platform/OpenGL/OpenGLRendererApi.h>


namespace Rayer {


	void OpenGLRendererApi::Init() {

	
		// Enable backface culling
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);


		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);

	}

	void OpenGLRendererApi::SetClearColor(const glm::vec4& color) {

		
		glClearColor(color.x, color.y, color.z, color.w);

	}

	void  OpenGLRendererApi::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {

		glViewport(x, y, width, height);

	}

	void OpenGLRendererApi::Clear() {

		glClear(GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);
		

	}

	void OpenGLRendererApi::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) {

		
		vertexArray->Bind();

	
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		
	
	}



	void OpenGLRendererApi::DrawWireframe(const Ref<VertexArray>& vertexArray, uint32_t count) {

		glDisable(GL_CULL_FACE);

		vertexArray->Bind();

		// Enable wireframe mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);

		// Disable wireframe mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}


	void OpenGLRendererApi::DrawLine(const Ref<VertexArray>& vertexArray, uint32_t count) {


		vertexArray->Bind();


		glDrawElements(GL_LINES, count, GL_UNSIGNED_INT, nullptr);

	}
}