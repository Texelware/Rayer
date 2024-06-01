#pragma once
#include <Rayer/RenderEngine/RenderingPrimitives/Framebuffer.h>


namespace Rayer {

	class OpenGLFrameBuffer : public Framebuffer {

	public:

		OpenGLFrameBuffer(const FramebufferSpecification& spec);

		virtual void Bind() override;
		virtual void Unbind() override;

		
		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;

		virtual void ClearAttachment(uint32_t attachmentIndex, int value) override;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override {  return m_ColorAttachments[index]; }
		virtual uint32_t GetDepthAttachmentID() const { return m_DepthAttachment; }

		virtual const FramebufferSpecification& GetSpecification() const override { return bufferSpecification; }

		void Invalidate();
		
	private:
		//Framebuffer specification
		FramebufferSpecification bufferSpecification;


		//Framebuffer ID
		uint32_t m_RendererID = 0;

		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;
		FramebufferTextureSpecification m_DepthAttachmentSpecification = FramebufferTextureFormat::None;

		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment = 0;

	};

}