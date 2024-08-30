#include <Rayer/Core/Assert.h>
#include "OpenGLFrameBuffer.h"

#include <glad/glad.h>

namespace Rayer {

	static const uint32_t s_MaxFramebufferSize = 8192;

	namespace Utils {

		static GLenum TextureTarget(bool multisampled)
		{
			return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}

		static void CreateTextures(bool multisampled, uint32_t* outID, uint32_t count)
		{
			glCreateTextures(TextureTarget(multisampled), count, outID);
		}

		static void BindTexture(bool multisampled, uint32_t id)
		{
			glBindTexture(TextureTarget(multisampled), id);
		}

		static void AttachColorTexture(uint32_t id, int samples, GLenum internalFormat, GLenum format, uint32_t width, uint32_t height, int index)
		{
			bool multisampled = samples > 1;
			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
		}

		static void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
		{
			bool multisampled = samples > 1;
			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
			}
			else
			{
				glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);
			


				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);

		}

		static bool IsDepthFormat(FramebufferTextureFormat format)
		{
			switch (format)
			{
			case FramebufferTextureFormat::DEPTH24STENCIL8:  return true;
			case FramebufferTextureFormat::DEPTH_COMPONENT24: return true;
			}

			return false;
		}

		static GLenum RayerFBTextureFormatToGL(FramebufferTextureFormat format)
		{
			switch (format)
			{
			case FramebufferTextureFormat::RGBA8:       return GL_RGBA8;
			case FramebufferTextureFormat::RED_INTEGER: return GL_RED_INTEGER;
			}

			RAYER_CORE_ASSERT(false, "Unknown framebuffer texture format");
			return 0;
		}

	}

	OpenGLFrameBuffer::OpenGLFrameBuffer(const FramebufferSpecification& spec)
		: bufferSpecification(spec)
	{
		//bufferSpecification.Width = 1280;
		//bufferSpecification.Height = 720;

		for (auto spec : bufferSpecification.Attachments.Attachments)
		{
			if (!Utils::IsDepthFormat(spec.TextureFormat))
				m_ColorAttachmentSpecifications.emplace_back(spec);
			else
				m_DepthAttachmentSpecification = spec;
		}

		Invalidate();
	}
	void OpenGLFrameBuffer::Invalidate()
	{
		if (m_RendererID)
		{
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
			glDeleteTextures(1, &m_DepthAttachment);

			m_ColorAttachments.clear();
			m_DepthAttachment = 0;
		}

		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		bool multisample = bufferSpecification.Samples > 1;

		// Attachments
		if (m_ColorAttachmentSpecifications.size())
		{
			m_ColorAttachments.resize(m_ColorAttachmentSpecifications.size());
			Utils::CreateTextures(multisample, m_ColorAttachments.data(), m_ColorAttachments.size());

			for (size_t i = 0; i < m_ColorAttachments.size(); i++)
			{
				Utils::BindTexture(multisample, m_ColorAttachments[i]);
				switch (m_ColorAttachmentSpecifications[i].TextureFormat)
				{
				case FramebufferTextureFormat::RGBA8:
					Utils::AttachColorTexture(m_ColorAttachments[i], bufferSpecification.Samples, GL_RGBA8, GL_RGBA, bufferSpecification.Width, bufferSpecification.Height, i);
					break;
				case FramebufferTextureFormat::RED_INTEGER:
					Utils::AttachColorTexture(m_ColorAttachments[i], bufferSpecification.Samples, GL_R32I, GL_RED_INTEGER, bufferSpecification.Width, bufferSpecification.Height, i);
					break;
				
				}
			}
		}

		if (m_DepthAttachmentSpecification.TextureFormat != FramebufferTextureFormat::None)
		{
			Utils::CreateTextures(multisample, &m_DepthAttachment, 1);
			Utils::BindTexture(multisample, m_DepthAttachment);
			switch (m_DepthAttachmentSpecification.TextureFormat)
			{
			case FramebufferTextureFormat::DEPTH24STENCIL8:
				Utils::AttachDepthTexture(m_DepthAttachment, bufferSpecification.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, bufferSpecification.Width, bufferSpecification.Height);
				break;
			case FramebufferTextureFormat::DEPTH_COMPONENT24:
				Utils::AttachDepthTexture(m_DepthAttachment, bufferSpecification.Samples, GL_DEPTH_COMPONENT24, GL_DEPTH_ATTACHMENT, bufferSpecification.Width, bufferSpecification.Height);
				break;

			}
		}

		if (m_ColorAttachments.size() > 1)
		{
			RAYER_CORE_ASSERT(m_ColorAttachments.size() < 4, "We don't support more than 4 color attachments");
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };

			glDrawBuffers(m_ColorAttachments.size(), buffers);



		}

		if (m_DepthAttachment != 0) {

			glDrawBuffer(m_DepthAttachment);


		}

		else if (m_ColorAttachments.empty())
		{
			// Only depth-pass
			glDrawBuffer(GL_NONE);
		}

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
			std::string error;
			switch (status) {
			case GL_FRAMEBUFFER_UNDEFINED: error = "GL_FRAMEBUFFER_UNDEFINED"; break;
			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: error = "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT"; break;
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: error = "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT"; break;
			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER: error = "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER"; break;
			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER: error = "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER"; break;
			case GL_FRAMEBUFFER_UNSUPPORTED: error = "GL_FRAMEBUFFER_UNSUPPORTED"; break;
			case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE: error = "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE"; break;
			case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS: error = "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS"; break;
			default: error = "Unknown error"; break;
			}
			RAYER_CORE_ASSERT(false, "Framebuffer is incomplete: " << error);
		}


		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	}

	void OpenGLFrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	int OpenGLFrameBuffer::ReadPixel(uint32_t attachmentIndex, int x, int y)
	{
		RAYER_CORE_ASSERT(attachmentIndex < m_ColorAttachments.size(), "Not a valid index")

		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
		int pixelData;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
		return pixelData;
	}

	void OpenGLFrameBuffer::ClearAttachment(uint32_t attachmentIndex, int value)
	{
		RAYER_CORE_ASSERT(attachmentIndex < m_ColorAttachments.size(), "Not a valid index")

			auto& spec = m_ColorAttachmentSpecifications[attachmentIndex];
		glClearTexImage(m_ColorAttachments[attachmentIndex], 0,
			Utils::RayerFBTextureFormatToGL(spec.TextureFormat), GL_INT, &value);
	}

	void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0); // Unbind framebuffer before resizing

		bufferSpecification.Width = width;
		bufferSpecification.Height = height;

		Invalidate();
	}

} // namespace Rayer
