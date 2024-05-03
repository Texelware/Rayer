#pragma once

#include <glad/glad.h>
#include <rpch.h>
#include <Rayer/RenderEngine/RenderingPrimitives/Shader.h>

namespace Rayer {

    class OpenGLShader : public Shader {

    public:

        OpenGLShader(std::string vertexShaderPath, std::string fragmentShaderPath);

        virtual void Bind() const override;

        virtual void Unbind() const override;

        virtual int GetID() const override;

        // Shader creation methods
        int CreateShader(std::string vertexShaderPath, std::string fragmentShaderPath);
        int CompileShader(GLenum shaderType, std::string shaderSource);

        // Overridden uniform setting functions
        virtual void SetUniformMat4(const std::string& name, const glm::mat4& matrix) override;
        virtual void SetUniformFloat(const std::string& name, float value) override;
        virtual void SetUniformInt(const std::string& name, int value) override;

    private:

        int programID;

    };

}
