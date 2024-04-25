#pragma once

#include <Rayer/RenderEngine/RenderingPrimitives/Buffer.h>

namespace Rayer {

	class OpenGLVertexBuffer : public VertexBuffer {

		public:	
			OpenGLVertexBuffer() {}
			OpenGLVertexBuffer(float* data, uint32_t size);

			virtual void Bind() const override;
			virtual void Unbind() const override;

		
			virtual BufferLayout& GetBufferLayout() override { return m_Layout; }
			virtual void SetBufferLayout(const BufferLayout& layout) override { m_Layout = layout; }
	
	private:

		BufferLayout m_Layout;
		uint32_t m_RendererID;

	};

	class OpenGLIndexBuffer : public IndexBuffer {

		public:
			OpenGLIndexBuffer() {}
			OpenGLIndexBuffer(unsigned int *data, uint32_t count);

			virtual void Bind() const override;
			virtual void Unbind() const override;

			virtual int GetCount() const override { return m_Count; }

	private:

		uint32_t m_RendererID;
		uint32_t m_Count;
	};

	
}