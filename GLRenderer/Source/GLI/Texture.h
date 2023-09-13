#pragma once

#include "GLObject.h"

#include <string>

namespace GLI
{
	class Texture : protected GLObject
	{
	private:

		std::string filepath;
		unsigned char* data{};
		int width{};
		int height{};
		int channels{};

	public:

		Texture(const std::string& filepath);
		virtual ~Texture() override;

		virtual void Activate(unsigned int slot = 0) const;
		virtual void Unbind() const override;

		inline std::string GetFilepath() const { return filepath; }
		inline unsigned char* GetData() const { return data; }
		inline int GetWidth() const { return width; }
		inline int GetHeight() const { return height; }
		inline int GetChannels() const { return channels; }
		
		static unsigned int LoadTexture(
			const std::string& filepath,
			int* width = nullptr,
			int* height = nullptr,
			int* channels = nullptr,
			unsigned char* data = nullptr
		);
	
	private:

		virtual void Bind() const override;
	};

}

