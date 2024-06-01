
#include <stb_image.h>
#include "OpenGLTexture.h"


namespace Rayer {

	
	OpenGLTexture2D::OpenGLTexture2D(const std::filesystem::path& _path) {

		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);

		stbi_uc* data = nullptr;

		data = stbi_load(_path.string().c_str(), &width, &height, &channels, 0);

	

		if (data) {

			if (data) {
				switch (channels) {
				case 3:
					internal_format = GL_RGB8;
					data_format = GL_RGB;
					break;
				case 4:
					internal_format = GL_RGBA8;
					data_format = GL_RGBA;
					break;
				default:
					std::cerr << "Unsupported number of channels: " << channels << std::endl;
					stbi_image_free(data);
					return;
				}
			}

			isLoaded = true;

			m_Width = width;
			m_Height = height;

			glGenTextures(1, &m_RendererID);
			glBindTexture(GL_TEXTURE_2D, m_RendererID);

			// Set texture parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			// Set texture data
			glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, data_format, GL_UNSIGNED_BYTE, data);

			

			// Generate mipmaps
			glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(data);

			#ifdef RAYER_DEBUG
			
					std::cout << "Texture loaded with id : " << m_RendererID << std::endl;
			
			#endif // RAYER_DEBUG

		}

		else {

			#ifdef RAYER_DEBUG
				std::cout << "Failed to load texture !" << std::endl;
			#endif // RAYER_DEBUG
		}
	}


	OpenGLTexture2D::OpenGLTexture2D(const std::string& _path) {


		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);

		stbi_uc* data = nullptr;

		data = stbi_load(_path.c_str(), &width, &height, &channels, 0);



		if (data) {

			if (data) {
				switch (channels) {
				case 3:
					internal_format = GL_RGB8;
					data_format = GL_RGB;
					break;
				case 4:
					internal_format = GL_RGBA8;
					data_format = GL_RGBA;
					break;
				default:
					std::cerr << "Unsupported number of channels: " << channels << std::endl;
					stbi_image_free(data);
					return;
				}
			}

			isLoaded = true;

			m_Width = width;
			m_Height = height;

			glGenTextures(1, &m_RendererID);
			glBindTexture(GL_TEXTURE_2D, m_RendererID);

			// Set texture parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			// Set texture data
			glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, data_format, GL_UNSIGNED_BYTE, data);



			// Generate mipmaps
			glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(data);

			#ifdef RAYER_DEBUG

				std::cout << "Texture loaded with id : " << m_RendererID << std::endl;

			#endif // RAYER_DEBUG

		}

		else {

			#ifdef RAYER_DEBUG
				std::cout << "Failed to load texture !" << std::endl;
			#endif // RAYER_DEBUG
		}
	}

	void OpenGLTexture2D::Bind(uint32_t slot) {

		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

	}

	uint32_t OpenGLTexture2D::GetRendererID() const {

		return m_RendererID;

	}

}