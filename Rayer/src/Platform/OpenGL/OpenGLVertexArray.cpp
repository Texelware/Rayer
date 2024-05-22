#include <glad/glad.h>
#include <Platform/OpenGL/OpenGLVertexArray.h>

namespace Rayer {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Mat3:     return GL_FLOAT;
		case ShaderDataType::Mat4:     return GL_FLOAT;
		case ShaderDataType::Int:      return GL_INT;
		case ShaderDataType::Int2:     return GL_INT;
		case ShaderDataType::Int3:     return GL_INT;
		case ShaderDataType::Int4:     return GL_INT;
		case ShaderDataType::Bool:     return GL_BOOL;
		}

		RAYER_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

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

		for (const auto& element : vb->GetBufferLayout()) {
			glEnableVertexAttribArray(loc);
			glVertexAttribPointer(loc, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized, vb->GetBufferLayout().GetStride(), 
				(const void*)element.Offset);
			loc++;
		}

		m_VertexBuffer = vb;

		// It's a good idea to unbind the VAO after setting up vertex attributes
		glBindVertexArray(0);

	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& ib) {
		

		glBindVertexArray(m_RendererID);
		ib->Bind();
		m_IndexBuffer = ib;
		glBindVertexArray(0);


	}

}