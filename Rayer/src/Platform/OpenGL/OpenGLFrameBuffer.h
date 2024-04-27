#pragma once
#include <Rayer/RenderEngine/RenderingPrimitives/Framebuffer.h>


namespace Rayer {

	class OpenGLFrameBuffer : public Framebuffer {

	public:

		OpenGLFrameBuffer(const FrameBufferSpecification& spec);

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual uint32_t GetColorAttachmentID() const override;

		virtual void Resize(uint32_t width, uint32_t height) override;

		void Invalidate();
		
	private:
		//Framebuffer specification
		FrameBufferSpecification bufferSpecification;

		//Color attachment ID
		uint32_t colorAttachmentID;

		//Framebuffer ID
		uint32_t m_rendererID = 0;

	};

}