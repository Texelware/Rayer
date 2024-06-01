#pragma once

#include <Rayer/Spheremap/Spheremap.h>

namespace Rayer {

	class OpenGLSpheremap : public Spheremap {

	public:

		OpenGLSpheremap(const std::filesystem::path& _path);

		virtual uint32_t GetRendererID() const override { return m_RendererID; }
		virtual void Bind(uint32_t slot)  override;

		virtual void Invalidate(const std::filesystem::path& _path) override;

	private:

		uint32_t m_RendererID;
	};

}