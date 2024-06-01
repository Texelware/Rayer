#pragma once
#include <rpch.h>
#include <Rayer/Core/Core.h>

#include <glm/glm.hpp>

#define RAYER_ALBEDO_SLOT 1
#define RAYER_NORMAL_SLOT 2
#define RAYER_ENVIRONMENT_MAP_SLOT 9
#define RAYER_SHADOW_MAP_SLOT 10

namespace Rayer {

	class Shader {

	public:

		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual int GetID() const = 0;

		virtual void SetUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;

		virtual void SetUniformFloat(const std::string& name, float value) = 0;
		virtual void SetUniformFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetUniformFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetUniformInt(const std::string& name, int value) = 0;
		virtual void SetUniformUnsignedInt(const std::string& name, unsigned int value) = 0;
		virtual void SetUniformBool(const std::string& name, bool value) = 0;

		static Scope<Shader> Create(std::string vertexShaderPath, std::string fragmentShaderPath);

	};

}
