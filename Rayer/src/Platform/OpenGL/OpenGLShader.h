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

		//Shader creation methods
		int CreateShader(std::string vertexShaderPath, std::string fragmentShaderPath);
		int CompileShader(GLenum shaderType, std::string shaderSource);


	private:

		int programID;

	};

}