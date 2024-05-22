#pragma once
#include <glad/glad.h>
#include <Rayer/RenderEngine/RenderingPrimitives/Texture.h>

namespace Rayer {

	class OpenGLTexture2D : public Texture2D {

	public:
		OpenGLTexture2D(const std::filesystem::path& _path);
		OpenGLTexture2D(const std::string& _path);

		virtual uint32_t GetRendererID() const override;
		virtual void Bind(uint32_t slot = 0) override;
		


	private:

		uint32_t m_RendererID;


		int m_Width, m_Height;
		bool isLoaded { false };

		GLenum internal_format, data_format;

	};

}