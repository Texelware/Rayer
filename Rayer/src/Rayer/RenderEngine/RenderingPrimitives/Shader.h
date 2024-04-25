#pragma once
#include <rpch.h>
#include <Rayer/Core/Core.h>

namespace Rayer {

	class Shader {

	public:

		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual int GetID() const = 0;

		static Scope<Shader> Create(std::string vertexShaderPath, std::string fragmentShaderPath);
		
	};

}