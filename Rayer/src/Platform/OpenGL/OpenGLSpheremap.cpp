#include "OpenGLSpheremap.h"
#include <glad/glad.h>
#include <Rayer/Filesystem/FileSystem.h>
#include <stb_image.h>
#include <iostream>

namespace Rayer {

    OpenGLSpheremap::OpenGLSpheremap(const std::filesystem::path& _path) {
        

        Invalidate(_path);

    }

    void OpenGLSpheremap::Bind(uint32_t slot) {

        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }


    void OpenGLSpheremap::Invalidate(const std::filesystem::path& _path) {

        if (m_RendererID) {

			glDeleteTextures(1, &m_RendererID);
        }

        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);



        int width, height, channels;
        stbi_set_flip_vertically_on_load(true);

        stbi_uc* data = nullptr;



        data = stbi_load(_path.string().c_str(), &width, &height, &channels, 0);



        if (data) {


            // Set texture parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

            // Set texture data
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

            glGenerateMipmap(GL_TEXTURE_2D);

            stbi_image_free(data);

        }

        else {

            std::cout << "Failed to load texture : " << stbi_failure_reason() << std::endl;

        }

    }
}
