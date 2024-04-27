#pragma once
#include <Rayer/Core/Core.h>
#include <rpch.h>


namespace Rayer {

	struct FrameBufferSpecification {

		uint32_t width;
		uint32_t height;	

	};


	class Framebuffer {

	public:

		virtual ~Framebuffer() {}

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32_t GetColorAttachmentID() const = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;


		static Ref<Framebuffer> Create(const FrameBufferSpecification& spec);
	};

}