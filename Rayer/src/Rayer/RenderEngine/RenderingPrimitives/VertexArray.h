#pragma once
#include <Rayer/Core/Core.h>
#include <Rayer/RenderEngine/RenderingPrimitives/Buffer.h>

namespace Rayer {

	class VertexArray {

	public:

		~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetVertexBuffer(const Ref<VertexBuffer>& vb) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& ib) = 0;

		virtual Ref<VertexBuffer> GetVertexBuffer() const = 0;
		virtual Ref<IndexBuffer> GetIndexBuffer() const = 0;

		static Ref<VertexArray> Create();


	};

}