#include <glad/glad.h>
#include <Rayer/Core/Application.h>
#include <Rayer/Core/Core.h>
#include <Platform/OpenGL/OpenGLRendererApi.h>


namespace Rayer {


	void OpenGLRendererApi::Init() {

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);
		
		
		glDepthMask(GL_TRUE);

		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	}

	void OpenGLRendererApi::SetClearColor(const glm::vec4& color) {

		
		glClearColor(color.x, color.y, color.z, color.w);

	}

	void  OpenGLRendererApi::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {

		glViewport(x, y, width, height);

	}

	void OpenGLRendererApi::Clear() {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	}
	
	void OpenGLRendererApi::ClearDepth() {

		glClear(GL_DEPTH_BUFFER_BIT);

	}


	void OpenGLRendererApi::DrawSkybox(const Ref<VertexArray>& vertexArray, uint32_t count) {


		
		// Cull the front faces to render inside of the cube (assuming inside-out view)
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);


		// Disable writing to the depth buffer
		glDepthMask(GL_FALSE);

		#ifdef  RAYER_DEBUG

			GLboolean depthMaskEnabled;
			glGetBooleanv(GL_DEPTH_WRITEMASK, &depthMaskEnabled);
		
			if (depthMaskEnabled) {
		
				std::cout << "Failed to disable writting to glDepthMask" << std::endl;
		
			}

		#endif //  RAYER_DEBUG

		

		// Set the depth function to allow drawing the skybox
		glDepthFunc(GL_LEQUAL);

		// Bind the vertex array containing the skybox geometry
		vertexArray->Bind();

		
		// Draw the skybox using indexed drawing
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);

		

		// Unbind the vertex array
		vertexArray->Unbind();
		
		
	}


	void OpenGLRendererApi::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count) {


		glDepthMask(GL_TRUE);

		// Enable backface culling
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		vertexArray->Bind();

		

		glDepthFunc(GL_LESS);
		


		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);

		vertexArray->Unbind();
		
	
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


	void OpenGLRendererApi::BindTextureToUnit(uint32_t slot, uint32_t texID) {
		
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, texID);

	}
}