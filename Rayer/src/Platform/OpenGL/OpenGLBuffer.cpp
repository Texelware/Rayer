#include <Rayer/Core/Application.h>
#include <glad/glad.h>
#include <Platform/OpenGL/OpenGLBuffer.h>

namespace Rayer {


	/////////Vertex Buffer//////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* data, uint32_t size) {

		
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	}

	void OpenGLVertexBuffer::Bind() const {
		
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

	}


	void OpenGLVertexBuffer::Unbind() const {
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	////////Index Buffer//////////


	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int* data, uint32_t count) {
		
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);

	}

	void OpenGLIndexBuffer::Bind() const {
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);

	}

	void OpenGLIndexBuffer::Unbind() const {
	
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

	
}