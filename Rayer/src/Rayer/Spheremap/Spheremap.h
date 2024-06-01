#pragma once

#include <Rayer/Core/Core.h>
#include <rpch.h>
#include <filesystem>

namespace Rayer {

	class Spheremap {

	public:

		virtual uint32_t GetRendererID() const = 0;
		virtual void Bind(uint32_t slot = 9) = 0;

		virtual void Invalidate(const std::filesystem::path& _path) = 0;

		static Ref<Spheremap> Create(const std::filesystem::path& _path);

	
	};

}