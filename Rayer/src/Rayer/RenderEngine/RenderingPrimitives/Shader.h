#pragma once
#include <rpch.h>
#include <Rayer/Core/Core.h>

#include <glm/glm.hpp>

namespace Rayer {

	class Shader {

	public:

		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual int GetID() const = 0;

		virtual void SetUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
		virtual void SetUniformFloat(const std::string& name, float value) = 0;
		virtual void SetUniformInt(const std::string& name, int value) = 0;

		static Scope<Shader> Create(std::string vertexShaderPath, std::string fragmentShaderPath);

	};

}
