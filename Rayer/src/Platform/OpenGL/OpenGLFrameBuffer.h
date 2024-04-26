#pragma once
#include <Rayer/RenderEngine/RenderingPrimitives/Framebuffer.h>


namespace Rayer {

	class OpenGLFrameBuffer : public Framebuffer {

	public:

		OpenGLFrameBuffer(const FrameBufferSpecification& spec);

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual uint32_t GetColorAttachmentID() const override;

		void Invalidate();
		
	private:

		FrameBufferSpecification bufferSpecification;

		uint32_t colorAttachmentID;

		uint32_t m_rendererID;

	};

}