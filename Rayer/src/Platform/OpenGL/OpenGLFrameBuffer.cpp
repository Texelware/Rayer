#include <glad/glad.h>
#include <Rayer/Core/Assert.h>
#include "OpenGLFrameBuffer.h"

namespace Rayer {


	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& spec) : bufferSpecification(spec) {

		Invalidate();
	}

	void OpenGLFrameBuffer::Invalidate() {
		
		if (m_rendererID != 0) {

			glDeleteFramebuffers(1, &m_rendererID);
			glDeleteTextures(1, &colorAttachmentID);

		}

		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_FRAMEBUFFER, m_rendererID);

		glGenTextures(1, &colorAttachmentID);
		glBindTexture(GL_TEXTURE_2D, colorAttachmentID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bufferSpecification.width, bufferSpecification.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, colorAttachmentID, 0);

		
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			
			RAYER_CORE_ASSERT(false, "There is some issue with framebuffer!");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	void OpenGLFrameBuffer::Bind() {

		glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);

	}

	void OpenGLFrameBuffer::Unbind() {

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	uint32_t OpenGLFrameBuffer::GetColorAttachmentID() const {

		return colorAttachmentID;

	}


	void OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height) {

		bufferSpecification.width = width;
		bufferSpecification.height = height;


		Invalidate();
	}
	



}