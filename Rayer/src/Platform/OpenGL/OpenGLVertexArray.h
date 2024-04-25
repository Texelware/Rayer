#pragma once
#include <Rayer/Core/Core.h>
#include <Rayer/RenderEngine/RenderingPrimitives/VertexArray.h>

namespace Rayer {

	class OpenGLVertexArray : public VertexArray {


	public:

		OpenGLVertexArray();

		~OpenGLVertexArray();


		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetVertexBuffer(const Ref<VertexBuffer>& vb) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& ib) override;

		virtual Ref<VertexBuffer> GetVertexBuffer() const override { return m_VertexBuffer; }
		virtual Ref<IndexBuffer> GetIndexBuffer() const override { return m_IndexBuffer; }


	private:

		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer>  m_IndexBuffer;
		
		uint32_t m_RendererID;

	};

}