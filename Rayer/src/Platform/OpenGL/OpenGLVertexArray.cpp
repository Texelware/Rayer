#include <glad/glad.h>
#include <Platform/OpenGL/OpenGLVertexArray.h>

namespace Rayer {

	OpenGLVertexArray::OpenGLVertexArray() {

		
		glGenVertexArrays(1, &m_RendererID);
		
	}


	OpenGLVertexArray::~OpenGLVertexArray() {

		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const {
		
		
		glBindVertexArray(m_RendererID);
		

	}


	void OpenGLVertexArray::Unbind() const {
		
		glBindVertexArray(0);

	}

	void OpenGLVertexArray::SetVertexBuffer(const Ref<VertexBuffer>& vb) {
		
		
		glBindVertexArray(m_RendererID);
		vb->Bind();

		int loc = 0;

		for (auto element : vb->GetBufferLayout()) {

			glEnableVertexAttribArray(loc);
			glVertexAttribPointer(loc, element.Size, GL_FLOAT, element.Normalized, vb->GetBufferLayout().GetStride(), (const void*)element.Offset);
			loc++;
		}


		m_VertexBuffer = vb;

	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& ib) {
		

		glBindVertexArray(m_RendererID);
		ib->Bind();
		m_IndexBuffer = ib;


	}

}