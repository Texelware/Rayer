#include <glad/glad.h>
#include "OpenGLFrameBuffer.h"

namespace Rayer {


	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& spec) : bufferSpecification(spec) {

		Invalidate();
	}

	void OpenGLFrameBuffer::Invalidate() {
		
		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_FRAMEBUFFER, m_rendererID);

		glGenTextures(1, &colorAttachmentID);
		glBindTexture(GL_TEXTURE_2D, colorAttachmentID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bufferSpecification.width, bufferSpecification.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, colorAttachmentID, 0);

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



}