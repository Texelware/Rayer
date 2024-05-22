#pragma once

#include <rpch.h>
#include <Rayer/Core/Core.h>
#include <filesystem>

namespace Rayer {

	class Texture {

	public:

		virtual ~Texture() {}

		virtual uint32_t GetRendererID() const = 0;

		virtual void Bind(uint32_t slot) = 0;

	};


	class Texture2D : public Texture {

	public:
		static Ref<Texture2D> Create(const std::filesystem::path& _path);
		static Ref<Texture2D> Create(const std::string& _path);
	};

}